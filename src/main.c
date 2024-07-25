#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "entity.h"
#include "time.h"
#include "renderer.h"
#include "SDL.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Entity* entity;
Time time;

static void free_memory();

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
    game_is_running = initialize_window(&window, &renderer);
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
        render(renderer, entity);
        delay_frame(&time);
    }

    free_memory();
    destroy_window(window, renderer);
    
    return 0;
}