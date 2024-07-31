#ifndef TEXT_H
#define TEXT_H

#include "SDL_ttf.h"
#include "SDL_pixels.h"

#define TEXT_BUFFER_SIZE 256

struct SDL_Renderer;

typedef struct font_s
{
    char player_score_text_buffer[TEXT_BUFFER_SIZE];
    int ptsize;
    TTF_Font* font;
    SDL_Color text_color;
} Font;

void initialize_text();
void render_text(SDL_Renderer* renderer, int playerScore, int x, int y);
void free_text_memory();

#endif