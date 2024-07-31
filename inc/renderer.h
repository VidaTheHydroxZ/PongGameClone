#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "entity.h"
#include "SDL.h"

typedef struct font_s Font;



int32_t initialize_window();
void render();
void destroy_window();
void get_entity_for_renderer();

#endif