#include "visual.h"

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

WINDOW *create_window(int start_y, int start_x, int height, int width) {
  WINDOW *local_window;

  local_window = newwin(height, width, start_y, start_x);

  return local_window;
}

WINDOW *create_text_window(char *text, int start_y, int start_x, int height,
                           int width) {
  // calcule to start text
  const int start_text_x = (width - strlen(text)) / 2;
  WINDOW *local_window = create_window(start_y, start_x, height, width);

  // window borders
  wborder(local_window, '|', '|', '-', '-', '-', '-', '-', '-');

  // show the text
  mvwprintw(local_window, (int)(height / 2), start_text_x, "%s", text);

  return local_window;
}

void print_menu() {
  WINDOW *local_window =
      create_text_window(GAME_NAME, 0, 0, MENU_HEIGHT, MENU_WIDTH);
  wrefresh(local_window);
}
