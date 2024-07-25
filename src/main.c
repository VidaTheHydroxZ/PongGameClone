#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "entity.h"
#include "time.h"
#include "SDL.h"

int32_t game_is_running;
SDL_Window* window;
SDL_Renderer* renderer;
Entity* entity;
Time time;

static void free_memory();

int32_t initialize_window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return INIT_FAILED;
    }
        window = SDL_CreateWindow(
        "BlobGame", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_BORDERLESS
        );
    if (!window) 
    {
        fprintf(stderr, "Error creating SDL Window.\n");
        return INIT_FAILED;
    }
        renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return INIT_FAILED;
    }
    return INIT_SUCCESS;
}

void update()
{
    calculate_delta_time(&time);
    ball_movement(entity, &time);
    check_ball_player_collision(entity);
    check_ball_walls_collision(entity);
}

void process_input()
{
    SDL_Event event;
    SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game_is_running = 0;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        game_is_running = 0;
    }
    if (state[SDL_SCANCODE_W] && entity->player1->rectangle->y > 0)
    {
        move_player_one_up(entity, &time);
    }
    if (state[SDL_SCANCODE_S] && (entity->player1->rectangle->y + entity->player1->rectangle->h) < WINDOW_HEIGHT)
    {
        move_player_one_down(entity, &time);
    }
    if (state[SDL_SCANCODE_K] && entity->player2->rectangle->y > 0)
    {
        move_player_two_up(entity, &time);
    }
    if (state[SDL_SCANCODE_L] && (entity->player2->rectangle->y + entity->player2->rectangle->h) < WINDOW_HEIGHT)
    {
        move_player_two_down(entity, &time);
    }
}

void setup()
{
    entity = (Entity*)malloc(sizeof(Entity));
    initialize_entities(entity);
    initialize_time(&time);
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, entity->ball->rectangle);
    SDL_RenderFillRect(renderer, entity->player1->rectangle);
    SDL_RenderFillRect(renderer, entity->player2->rectangle);

    // Present the screen
    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void free_memory()
{
    free(entity->ball->rectangle);
    free(entity->player1->rectangle);
    free(entity->player2->rectangle);

    free(entity->ball);
    free(entity->player1);
    free(entity->player2);
    
    free(entity);
}

int SDL_main (int argc, char* argv[])
{
    game_is_running = initialize_window();
    if (game_is_running != INIT_SUCCESS)
    {
        return -1;
    }
    setup();
    printf("Game is running...");
    while(game_is_running)
    {
        update();
        process_input();
        render();
        delay_frame(&time);
    }

    free_memory();
    destroy_window();
    
    return 0;
}