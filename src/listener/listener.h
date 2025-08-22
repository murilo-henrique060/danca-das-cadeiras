#ifndef LISTENER_H
#define LISTENER_H

#include <ncurses.h>

void listener_init();
void listener_wait(char key);
void listener_destroy();

#endif // LISTENER_H