#include "visual.h"

#include <ncurses.h>

WINDOW *create_window(int start_y, int start_x, int height, int width) {
  WINDOW *local_window;

  local_window = newwin(height, width, start_y, start_x);
  box(local_window, 0, 0);
  wrefresh(local_window);

  return local_window;
}

void print_menu() {
  WINDOW *local_window;
  local_window = create_window(0, 0, MENU_HEIGHT, MENU_WIDTH);

  printw("Dança das Cadeiras");
}
