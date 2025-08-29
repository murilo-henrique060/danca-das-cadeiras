#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "runtime.h"
#include "../visual/visual.h"

void init_game() {

  // init the ncurses
  initscr();
  // noecho();
  // curs_set(0);

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

void print_manual() {
  clear();

  char players_keys[] = PLAYER_KEYS;
  for (int i = 0; i < (int)sizeof(players_keys); i++)
    printw("Player(%d) irá usar a tecla: '%c'\n", i + 1, players_keys[i]);

  printw("Pressione qualquer tecla para continuar.\n");
  refresh();
  getch();
}

int ask_player_number() {
  char response = '0';
  int choiced_number = -1;
  int i = 0;

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
  printw("Número de jogadores escolhido foi %d.\n", choiced_number);
  refresh();
  sleep(2);

  return choiced_number;
}

int get_number_of_players(unsigned char *players) {
  int counter = 0;
  unsigned char all_players[] = PLAYERS_ARRAY;

  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (all_players[i] & *players) // AND gate with players
      counter++;
  }

  return counter;
}

void remove_player(unsigned char *players, int removed_player) {
  *players = (*players & ~removed_player); // AND gate to remove a player
}

void add_player(unsigned char *players, int added_player) {
  *players |= added_player; // OR gate to add a player
}

unsigned short player_is_active(unsigned char *players, int current_player) {
  if (*players & current_player)
    return 1;
  else
    return 0;
}

unsigned char start_players(int number_of_players) {
  unsigned char players = 0;
  unsigned char all_players[] = PLAYERS_ARRAY;

  for (int i = 0; i < number_of_players; i++)
    players |= all_players[i]; // OR gate to activate player

  return players;
}

int get_player_ID(int player) {
  unsigned char all_players[] = PLAYERS_ARRAY;

  for (int i = 0; i < (int)sizeof(all_players); i++) {
    if (all_players[i] & player)
      return i + 1;
  }

  // if player doesn't exist
  exit(1);
}

char get_player_key(int player) {
  unsigned char all_players[] = PLAYERS_ARRAY;
  char keys[] = PLAYER_KEYS;

  for (int i = 0; i < (int)sizeof(all_players); i++) {
    if (all_players[i] & player)
      return keys[i];
  }

  // if the key doesn't exist
  exit(1);
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
