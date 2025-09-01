#include "listener/listener.h"
#include "runtime/runtime.h"
#include "semaphore/semaphore.h"
#include "visual/visual.h"

#include <locale.h>
#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @struct thread_args
 * @brief All arg to use in thread.
 * * Struct with args to use in thread.
 */
typedef struct thread_args {

  semaphore *sem;         ///< Pointer to shared main semaphore
  Listener *listener;     ///< Pointer to shared listener
  unsigned char *players; ///< Pointer to the shared bitmask of current players
  int player;             ///< current player
  unsigned char
      *safe_players;      ///< Pointer to the shared bitmask of winner players
  pthread_mutex_t *mutex; ///< Pointes to shared mutex to add safe players
  pthread_cond_t *cond;   ///< Pointer to shared condition to sync the thread

} thread_args;

/**
 * @brief Create args to player thread share.
 * * Will create args to a player thread to share the information.
 * @param sem Pointer to shared semaphore
 * @param listener Pointer to shared listener
 * @param players Pointer to active players
 * @param player Current thread player
 * @param safe_players Pointer to shared players safe
 * @param mutex Pointer to shared mutex of the threads
 * @param cond Pointer to condition to wake up a thread
 * @return Thread arguments.
 */
thread_args *create_thread_args(semaphore *sem, Listener *listener,
                                unsigned char *players, int player,
                                unsigned char *safe_players,
                                pthread_mutex_t *mutex, pthread_cond_t *cond);
/**
 * @brief The player will wait the current pressed key
 * * The player will will press the his key to continue in game
 * @param arg Thread args to comunicate with other threads
 */
void *wait_for_key(void *arg);

/**
 * @brief Cleanup the thread args
 * @param args Thread args with shared data
 */
void free_thread_args(thread_args *args);

/**
 * @brief Draw all safe players in round.
 * @param safe_players All safe players in round.
 * @param players_in_round Total number of players in current round.
 */
void draw_round_players_status(unsigned char *safe_players,
                               int players_in_round);

int main() {
  // to use accentuation
  // setlocale(LC_ALL, "");

  init_game();
  // create a listener
  Listener *listener = listener_init();

  // create a semaphore
  semaphore *sem = malloc(sizeof(semaphore));

  // show the main menu
  WINDOW *menu = print_menu();

  // running condition
  int running = 1;
  int number_of_players;

  // to compare players
  int all_players[] = PLAYERS_ARRAY;

  while (running) {
    // update menu
    clear();
    refresh();

    // refresh the window
    touchwin(menu);
    wrefresh(menu);

    number_of_players = ask_player_number();
    print_manual();

    // initialize the players
    unsigned char players = start_players(number_of_players);

    // ---- Loop until a player won the game (rounds) ----
    for (int i = number_of_players; i > 1; i--) {

      // round state
      int current_players_count = get_number_of_players(&players);

      // init the semaphore
      semaphore_init(sem, current_players_count - 1); // total players - 1

      unsigned char safe_players = 0; // all players are unsafe

      pthread_mutex_t round_mutex;
      pthread_cond_t round_cond;

      pthread_mutex_init(&round_mutex, NULL);
      pthread_cond_init(&round_cond, NULL);

      printw("Rodada com %d jogadores! Cadeiras: %d\n", current_players_count,
             sem->count);
      refresh();
      sleep(2);
      start_round_counter();

      char ch = ' ';
      nodelay(stdscr, TRUE); // Enable non-blocking input
      while (ch != EOF) ch = getch(); // Cleaning character buffer
      nodelay(stdscr, FALSE); // Disable non-blocking input

      // ---- Threads management ----
      pthread_t threads[current_players_count];
      thread_args *args[current_players_count];
      int thread_index = 0;

      for (int j = 0; j < MAX_PLAYERS; j++) {
        if (player_is_active(&players, all_players[j])) {
          args[thread_index] =
              create_thread_args(sem, listener, &players, all_players[j],
                                 &safe_players, &round_mutex, &round_cond);

          pthread_create(&threads[thread_index], NULL, wait_for_key,
                         args[thread_index]);
          thread_index++;
        }
      }

      pthread_mutex_lock(&round_mutex);
      while (get_number_of_players(&safe_players) < current_players_count - 1) {
        // sleep and wait to wake up by a signal
        pthread_cond_wait(&round_cond, &round_mutex);
        draw_round_players_status(
            &safe_players, current_players_count); // show all safe players
      }
      pthread_mutex_unlock(&round_mutex);

      // loser is only fliped bit
      int loser_player = players ^ safe_players;

      // unlock stopped thread
      semaphore_signal(sem);

      // ---- Wait the round finish ----
      // first won threads
      for (int j = 0; j < thread_index; j++) {
        pthread_join(threads[j], NULL);
        free_thread_args(args[j]);
      }

      printw("O Player(%d) foi eliminado!\n", get_player_ID(loser_player));
      printw("Aperte qualquer tecla.\n");
      refresh();
      getch();

      // update active players
      remove_player(&players, loser_player);

      pthread_mutex_destroy(&round_mutex);
      pthread_cond_destroy(&round_cond);
    }

    // ---- Winner Player ----
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (player_is_active(&players, all_players[i])) {
        clear();
        printw("O Player(%d) ganhou!!!\n", get_player_ID(all_players[i]));
        printw("Aperte qualquer botão.\n");
        refresh();
        getch();
        break;
      }
    }

    // ask if players want play again
    clear();
    printw("Gostaria de jogar novamente? [s/n]");
    refresh();
    char response = getch();
    if (response != 's')
      running = 0;
  }

  // Exit of the game
  listener_destroy(listener);
  semaphore_destroy(sem);
  delete_window(menu);
  exit_game();
  return 0;
}

thread_args *create_thread_args(semaphore *sem, Listener *listener,
                                unsigned char *players, int player,
                                unsigned char *safe_players,
                                pthread_mutex_t *mutex, pthread_cond_t *cond) {

  thread_args *args = (thread_args *)malloc(sizeof(thread_args));

  if (!args)
    return NULL;

  args->sem = sem;
  args->listener = listener;
  args->players = players;
  args->player = player;
  args->safe_players = safe_players;
  args->mutex = mutex;
  args->cond = cond;

  return args;
}

void *wait_for_key(void *arg) {

  // convert thread args
  thread_args *args = (thread_args *)arg;

  // wait the pressed key
  listener_wait(args->listener, get_player_key(args->player));

  // try get the semaphore
  semaphore_wait(args->sem);

  pthread_mutex_lock(args->mutex);

  int players_in_round = get_number_of_players(args->players);
  int safe_count = get_number_of_players(args->safe_players);

  // just winners run this code
  if (safe_count < players_in_round - 1) {
    add_player(args->safe_players, args->player);

    // signal to main thread
    pthread_cond_signal(args->cond);
  }

  pthread_mutex_unlock(args->mutex);

  return NULL;
}

void free_thread_args(thread_args *args) {
  if (args)
    free(args);
}

void draw_round_players_status(unsigned char *safe_players,
                               int players_in_round) {

  const int init_status_line = TIME_TO_START_ROUND + 1;

  // cleanup all status line
  for (int i = 0; i < players_in_round; i++) {
    move(init_status_line + i, 0);
    clrtoeol();
  }

  int current_line = 0;
  int all_players[] = PLAYERS_ARRAY;
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (player_is_active(safe_players, all_players[i]))
      mvprintw(init_status_line + current_line++, 0,
               "O Player(%d) está a salvo!\n", get_player_ID(all_players[i]));
  }
}
