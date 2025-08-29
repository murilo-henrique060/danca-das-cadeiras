#ifndef RUNTIME_H
#define RUNTIME_H

/**
 * @brief Maximal number of players in a match
 */
#define MAX_PLAYERS 5

/**
 * @brief Minimal number of players in a match
 */
#define MIN_PLAYERS 2

/**
 * @brief Time to counter init the round
 */
#define TIME_TO_START_ROUND 5

/**
 * @brief Bitmask to represent PLAYER(1)
 * * Bitmask: 0b00000001
 */
#define PLAYER_1 (1 << 0)

/**
 * @brief Bitmask to represent PLAYER(1)
 * * Bitmask: 0b00000010
 */
#define PLAYER_2 (1 << 1)

/**
 * @brief Bitmask to represent PLAYER(1)
 * * Bitmask: 0b00000100
 */
#define PLAYER_3 (1 << 2)

/**
 * @brief Bitmask to represent PLAYER(1)
 * * Bitmask: 0b00001000
 */
#define PLAYER_4 (1 << 3)

/**
 * @brief Bitmask to represent PLAYER(1)
 * * Bitmask: 0b00010000
 */
#define PLAYER_5 (1 << 4)

/**
 * @brief Shape of array with all player in order
 */
#define PLAYERS_ARRAY {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4, PLAYER_5}

/**
 * @brief Shape of array with all player keys in order
 */
#define PLAYER_KEYS {'a', 'd', 'g', 'j', 'l'}

/**
 * @brief Init the game.
 * * Will initialize the game engine.
 */
void init_game();

/**
 * @brief Exit of the game.
 * * Safety exit of the game engine.
 */
void exit_game();

/**
 * @brief Will print the manual of kaymaps
 */
void print_manual();

/**
 * @brief Ask to use how many player will play.
 * * Will show a message on Terminal and read the user response to return the
 * number of players.
 * @return Number of player of the game.
 */
int ask_player_number();

/**
 * @brief Get active players.
 * * Get how many players is in the game.
 * @param players Pointer of a number to represent active players.
 * @return Number of active players.
 */
int get_number_of_players(unsigned char *players);

/**
 * @brief Remove a player.
 * * Remove a player from active players.
 * @param players Pointer to a number wich represent active players.
 * @param removed_player Player to remove.
 */
void remove_player(unsigned char *players, int removed_player);

/**
 * @brief Add a player.
 * * Add a player from active players.
 * @param players Pointer to a number wich represent active players.
 * @param added_player Player to add.
 */
void add_player(unsigned char *players, int added_player);

/**
 * @brief Check a player.
 * * Check if the player is a active players.
 * @param players Pointer to a number to represent active players.
 * @param current_player Player to analyze.
 * @return 1 if player is in active players, else, return 0.
 */
unsigned short player_is_active(unsigned char *players, int current_player);

/**
 * @brief Initialize players.
 * * Will initialize all players.
 * @param players Number to represent active players.
 * @return All players activated.
 */
unsigned char start_players(int number_of_players);

/**
 * @brief ID of the player.
 * * Will get the player ID.
 * @param player Number to represent current players.
 * @return Player's ID.
 */
int get_player_ID(int player);

/**
 * @brief Get key of the player.
 * * Will get the key of the current player.
 * @param player Number to represent current players.
 * @return Key of the player.
 */
char get_player_key(int player);

/**
 * @brief Start a counter.
 * * Start a counter to start the round.
 */
void start_round_counter();

#endif // RUNTIME_H
