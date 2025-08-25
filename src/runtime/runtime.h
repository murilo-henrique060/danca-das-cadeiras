#ifndef RUNTIME_H
#define RUNTIME_H

#define MAX_PLAYERS 5
#define MIN_PLAYERS 2

/*
 * @brief Ask to use how many player will play.
 * * Will show a message on Terminal and read the user response to return the
 * number of players.
 * @return Number of player of the game.
 */
short ask_player_number();

/*
 * @brief Init the game.
 * * Will initialize the game engine.
 */
void init_game();

/*
 * @brief Exit of the game.
 * * Safety exit of the game engine.
 */
void exit_game();

#endif
