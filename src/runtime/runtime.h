#ifndef RUNTIME_H
#define RUNTIME_H

#define MAX_PLAYERS 5

#include "../semaphore/semaphore.h"

/*
 * @brief Ask to use how many player will play.
 * * Will show a message on Terminal and read the user response to return the
 * number of players.
 * @return Number of player of the game
 */
short ask_player_number(int x, int y);

/*
 * @brief Exit of the game
 * * Function to safety exit of the game
 * @param s The semaphore of the game
 */
void exit_game(semaphore **s);

#endif
