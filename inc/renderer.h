#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "entity.h"
#include "SDL.h"

extern int32_t game_is_running;

int32_t initialize_window(SDL_Window** window, SDL_Renderer** renderer);
void render(SDL_Renderer* renderer, Entity* entity);
void destroy_window(SDL_Window* window, SDL_Renderer* renderer);

#endif