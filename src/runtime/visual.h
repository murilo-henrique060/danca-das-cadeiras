#ifndef UI_H
#define UI_H

#include <ncurses.h>

#define GAME_NAME "Dança das Cadeiras"

const int MENU_HEIGHT = 3;
const int MENU_WIDTH = 60;

WINDOW *create_window(int start_y, int start_x, int height, int width);
WINDOW *create_text_window(char *text, int start_y, int start_x, int height,
                           int width);

/*
 * @brief Show the main menu.
 * * Show Main menu of the game.
 */
void print_menu();

#endif
