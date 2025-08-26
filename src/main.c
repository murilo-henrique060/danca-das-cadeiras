#include "listener/listener.h"
#include "runtime/runtime.h"
#include "semaphore/semaphore.h"
#include "visual/visual.h"

#include <ncurses.h>
#include <pthread.h>
#include <stdlib.h>

/*
 * @struct thread_args
 * @brief All arg to use in thread.
 * * Struct with args to use in thread.
 */
typedef struct thread_args {

  semaphore *sem;
  int player;
  unsigned work_is_done;

} thread_args;

thread_args *create_thread_args(semaphore *sem, int player);
void *wait_for_key(void *arg);

int main() {
  init_game();

  semaphore *sem = malloc(sizeof(semaphore));
  semaphore_init(sem, 1);

  WINDOW *menu = print_menu();

  int running = 1;
  short number_of_players;

  while (running) {
    clear();
    wrefresh(menu);
    number_of_players = ask_player_number();

    unsigned char players = start_players(number_of_players);

    for (unsigned short i = number_of_players; i > 0; i--) {
      // TODO: Players event
    }

    semaphore_destroy(sem);
    delete_window(menu);
    exit_game();
    return 0;
  }
}

thread_args *create_thread_args(semaphore *sem, int player) {

  thread_args *args = (thread_args *)malloc(sizeof(thread_args));

  if (!args)
    return NULL;

  args->sem = sem;
  args->player = player;
  args->work_is_done = 0;

  return args;
}

void *wait_for_key(void *arg) {

  thread_args *args = (thread_args *)arg;

  semaphore_wait(args->sem);
  listener_wait(get_player_key(args->player));

  printw("Player(%hu) pressed!\n", get_player_ID(args->player));

  semaphore_signal(args->sem);
  return NULL;
}
