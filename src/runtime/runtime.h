#ifndef RUNTIME_H
#define RUNTIME_H

#define MAX_PLAYERS 5
#define MIN_PLAYERS 2

#define PLAYER_1 (1 << 0) // 0b00001
#define PLAYER_2 (1 << 1) // 0b00010
#define PLAYER_3 (1 << 2) // 0b00100
#define PLAYER_4 (1 << 3) // 0b01000
#define PLAYER_5 (1 << 4) // 0b10000

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

/*
 * @brief Ask to use how many player will play.
 * * Will show a message on Terminal and read the user response to return the
 * number of players.
 * @return Number of player of the game.
 */
short ask_player_number();

/*
 * @brief Get active players.
 * * Get how many players is in the game.
 * @param players Number to represent active players.
 */
short get_number_of_players(unsigned char players);

/*
 * @brief Remove a player.
 * * Remove a player from active players.
 * @param players Number to represent active players.
 * @param removed_player Player to remove.
 */
unsigned char remove_player(unsigned char players, int removed_player);
#endif
