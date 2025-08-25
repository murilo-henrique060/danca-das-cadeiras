#ifndef RUNTIME_H
#define RUNTIME_H

#define MAX_PLAYERS 5
#define MIN_PLAYERS 2

#define TIME_TO_START_ROUND 5

#define PLAYER_1 (1 << 0) // 0b00000001
#define PLAYER_2 (1 << 1) // 0b00000010
#define PLAYER_3 (1 << 2) // 0b00000100
#define PLAYER_4 (1 << 3) // 0b00001000
#define PLAYER_5 (1 << 4) // 0b00010000

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
 * @return Number of active players.
 */
short get_number_of_players(unsigned char players);

/*
 * @brief Remove a player.
 * * Remove a player from active players.
 * @param players Number to represent active players.
 * @param removed_player Player to remove.
 * @return New active players.
 */
unsigned char remove_player(unsigned char players, int removed_player);

/*
 * @brief Check a player.
 * * Check if the player is a active players.
 * @param players Number to represent active players.
 * @param current_player Player to analyze.
 * @return 1 if player is in active players, else, return 0.
 */
unsigned short player_is_active(unsigned char players, int current_player);

/*
 * @brief Start a counter.
 * * Start a counter to start the round.
 */
void start_round_counter();

#endif
