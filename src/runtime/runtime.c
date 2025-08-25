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
