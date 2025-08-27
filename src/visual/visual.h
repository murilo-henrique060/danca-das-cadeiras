#ifndef VISUAL_H
#define VISUAL_H

#include <ncurses.h>

/**
 * @brief Name to show on print_menu().
 */
#define GAME_NAME "Dança das Cadeiras"

/**
 * @brief Main menu height
 */
#define MENU_HEIGHT 3

/**
 * @brief Main menu width
 */
#define MENU_WIDTH 60

/**
 * @brief Create a virtual window.
 * * Create a virtual window with ncurses.
 * @param start_y Start position in y axle.
 * @param start_x Start position in x axle.
 * @param height Height of the window.
 * @param windth Width of the window.
 * @return Return a new window.
 */
WINDOW *create_window(int start_y, int start_x, int height, int width);

/**
 * @brief Delete a window
 * * Use to delete a created window
 */
void delete_window(WINDOW *window);

/**
 * @brief Create a virtual window.
 * * Create a virtual window with ncurses.
 * @param text Text to show in window.
 * @param start_y Start position in y axle.
 * @param start_x Start position in x axle.
 * @param height Height of the window.
 * @param windth Width of the window.
 * @return Return a new window.
 */
WINDOW *create_text_window(char *text, int start_y, int start_x, int height,
                           int width);

/**
 * @brief Show the main menu.
 * * Show Main menu of the game.
 * @return Window with Game menu.
 */
WINDOW *print_menu();

#endif
