#include "text.h"
#include <stdio.h>

void initialize_text(Font* textFont)
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Failed to initialize SDL_TTF!\n");
        exit(1);
    }
    if (textFont == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for Font.\n");
        exit(1);
    }
    textFont->ptsize = 40;
    textFont->text_color.r = 255;
    textFont->text_color.g = 255;
    textFont->text_color.b = 255;
    textFont->text_color.a = 255;
}

void render_text(SDL_Renderer* renderer, Font* textFont, int playerScore, int x, int y)
{
    if (!renderer)
    {
        fprintf(stderr, "Error: Renderer is not initialized.\n");
        return;
    }

    if (!textFont)
    {
        fprintf(stderr, "Error: Font initialization failed.\n");
        return;
    }

    textFont->font = TTF_OpenFont("vendor/fonts/SuperPixel.ttf", textFont->ptsize);
    if (textFont->font == NULL)
    {
        printf("Font loading failed: %s\n", TTF_GetError());
        free(textFont);
        return;
    }
    snprintf(textFont->player_score_text_buffer, TEXT_BUFFER_SIZE, "Player Score: %d", playerScore);
    SDL_Surface* TextSurface = TTF_RenderText_Blended(textFont->font, textFont->player_score_text_buffer, textFont->text_color);
    if (TextSurface == NULL)
    {
        printf("Surface creation failed: %s\n", TTF_GetError());
        SDL_FreeSurface(TextSurface);
        TTF_CloseFont(textFont->font);
        free(textFont);
        return;
    }
    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);
    if (TextTexture == NULL)
    {
        printf("Texture creation failed: %s\n", TTF_GetError());
    }
    SDL_Rect textRect = {x, y, TextSurface->w, TextSurface->h};
    if(SDL_RenderCopy(renderer, TextTexture, NULL, &textRect) == -1)
    {
        printf("RenderCopy Failed: %s\n", TTF_GetError());
    }
}