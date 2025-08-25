#include <ctype.h>
#include <ncurses.h>
#include <unistd.h>

#include "../listener/listener.h"
#include "../semaphore/semaphore.h"
#include "runtime.h"
#include "visual.h"

short ask_player_number(int x, int y) {
  char response = '0';
  short choiced_number = -1;
  unsigned i = 0;

  do {
    clear();
    print_menu();

    if (i > 0)
      printw("\nNúmero de jogadores inválido: %c", response);

    printw("\nEscolha o número de jogadores (1 a %d): ", MAX_PLAYERS);

    refresh();

    response = getch();
    if (isdigit(response))
      choiced_number = response - '0'; // convert the char to int
    else
      choiced_number = -1;

    i++;

  } while (choiced_number < 2 || choiced_number > MAX_PLAYERS);

  printw("\n Número de jogadores escolhido foi %hu.\n", choiced_number);
  refresh();
  sleep(1);

  return choiced_number;
}

void exit_game(semaphore **s) {
  printw("Saindo do jogo...\n");
  refresh();
  listener_destroy();
  semaphore_destroy(*s);
}
