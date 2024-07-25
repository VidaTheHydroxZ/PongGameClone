#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "entity.h"
#include "SDL.h"

extern int32_t game_is_running;

int32_t initialize_window();
void render(Entity* entity);
void destroy_window();

#endif