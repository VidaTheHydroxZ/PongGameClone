#include "renderer.h"
#include "text.h"
#include "utils.h"
#include <stdio.h>

int32_t game_is_running;

SDL_Window* window;
SDL_Renderer* renderer;

int32_t initialize_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return INIT_FAILED;
    }
        window = SDL_CreateWindow(
        "PongGame", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_BORDERLESS
        );
    if (!window) 
    {
        fprintf(stderr, "Error creating SDL Window: %s\n", SDL_GetError());
        SDL_Quit();
        return INIT_FAILED;
    }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return INIT_FAILED;
    }
    return INIT_SUCCESS;
}

void render(Entity* entity, Font* textFont)
{

    if (!renderer) {
        fprintf(stderr, "Error: Renderer or Entity components are not initialized properly.\n");
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, entity->ball->rectangle);
    SDL_RenderFillRect(renderer, entity->player1->rectangle);
    SDL_RenderFillRect(renderer, entity->player2->rectangle);
    render_text(renderer, textFont, entity->player1->player_score, 50, 40);
    render_text(renderer, textFont, entity->player2->player_score, 1700, 40);

    // Present the screen
    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}