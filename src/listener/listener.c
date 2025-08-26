#include "listener.h"
#include <ncurses.h>

/**
 * @brief Initializes the listener.
 * 
 * This function sets up the ncurses library for capturing keyboard input.
 * It must be called before any other listener functions.
 */
void listener_init() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    keypad(stdscr, TRUE); // Enable function keys
}

/**
 * @brief Waits for a specific key press.
 * 
 * This function blocks until the specified key is pressed.
 * 
 * @param key The key to wait for.
 */
void listener_wait(char key) {
    int ch;
    while ((ch = getch()) != key);
}

/**
 * @brief Destroys the listener.
 * 
 * This function ends the ncurses mode.
 */
void listener_destroy() {
    endwin();
}
