#include <ctype.h>
#include <ncurses.h>
#include <unistd.h>

#include "runtime.h"
#include "visual.h"

void init_game() {

  // init the ncurses
  initscr();
  noecho();
  curs_set(0);

  // if the terminal has colors
  if (has_colors())
    start_color();

  // update the terminal
  refresh();
}

void exit_game() {

  // clear the terminal
  clear();

  // show to user the finish message
  printw("Saindo do jogo...\n");
  refresh();
  sleep(2);

  // finish the ncurses
  endwin();
}

short ask_player_number() {
  char response = '0';
  short choiced_number = -1;
  unsigned i = 0;

  do {

    // if it isn't not the first execution
    if (i > 0) {
      move(MENU_HEIGHT + 1, 0);
      clrtoeol(); // clear line

      move(MENU_HEIGHT + 2, 0);
      clrtoeol(); // clear line

      mvprintw(MENU_HEIGHT + 1, 0, "Número de jogadores inválido: %c",
               response);
      mvprintw(MENU_HEIGHT + 2, 0,
               "Escolha o número de jogadores (%d a %d): ", MIN_PLAYERS,
               MAX_PLAYERS);
    } else {

      mvprintw(MENU_HEIGHT + 1, 0,
               "Escolha o número de jogadores (%d a %d): ", MIN_PLAYERS,
               MAX_PLAYERS);
    }

    // update the terminal
    refresh();

    // wait the response
    response = getch();
    if (isdigit(response))
      choiced_number = response - '0'; // convert the char to int
    else
      choiced_number = -1;

    // update the execution counter
    i++;

    // while the choiced number is out of the interval
  } while (choiced_number < MIN_PLAYERS || choiced_number > MAX_PLAYERS);

  clear();
  printw("Número de jogadores escolhido foi %hu.\n", choiced_number);
  refresh();
  sleep(1);

  return choiced_number;
}

short get_number_of_players(unsigned char players) {
  unsigned short counter = 0;
  unsigned char all_players[] = {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4,
                                 PLAYER_5};

  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (all_players[i] & players) // AND gate with players
      counter++;
  }

  return counter;
}

unsigned char remove_player(unsigned char players, int removed_player) {
  return (players & ~removed_player); // AND gate to remove a player
}

unsigned short player_is_active(unsigned char players, int current_player) {
  if (players & current_player)
    return 1;
  else
    return 0;
}

void start_round_counter() {
  clear();
  printw("Iniciando próximo round (aperte qualquer tecla) \n");
  getch();

  for (int i = TIME_TO_START_ROUND; i > 0; i--) {
    printw("%d\n", i);
    refresh();
    sleep(1);
  }

  printw("APERTE!!!!\n");
  refresh();
}
