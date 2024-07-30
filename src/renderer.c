#include "renderer.h"
#include "text.h"
#include "utils.h"
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

Entity* rendererEntity = NULL;

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

void render()
{
    if (!renderer) {
        fprintf(stderr, "Error: Renderer or Entity components are not initialized properly.\n");
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, rendererEntity->ball->rectangle);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, rendererEntity->player1->rectangle);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, rendererEntity->player2->rectangle);
    render_text(renderer, rendererEntity->player1->player_score, 50, 40);
    render_text(renderer, rendererEntity->player2->player_score, 1700, 40);

    // Present the screen
    SDL_RenderPresent(renderer);
}

void get_entity_for_renderer()
{
    rendererEntity = get_entity();
    if (rendererEntity == NULL)
    {
        printf("No Entity could be assigned for renderer!\n");
        return;
    }
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}