#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "entity.h"
#include "SDL.h"

typedef struct font_s Font;

extern int32_t game_is_running;

int32_t initialize_window();
void render(Entity* entity, Font* textFont);
void destroy_window();

#endif