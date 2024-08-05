#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>

extern int32_t game_is_running;

void update();
void init();
void free_memory();
void quit_game();

#endif