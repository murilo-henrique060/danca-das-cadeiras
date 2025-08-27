#include "listener.h"
#include <ncurses.h>

void listener_init() {
    initscr(); // Initialize ncurses
    cbreak(); // Disable line buffering
    noecho(); // Disable echoing of typed characters
    keypad(stdscr, TRUE); // Enable function keys
}

void listener_wait(char key) {
    int ch;
    while ((ch = getch()) != key);
}

void listener_destroy() {
    endwin();
}
