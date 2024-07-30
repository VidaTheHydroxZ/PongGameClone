#include "input.h"
#include "entity.h"
#include "utils.h"
#include "SDL.h"

#include <stdio.h>

Entity* inputEntity = NULL;

int32_t game_is_running = 1;

void get_entity_for_input()
{
    inputEntity = get_entity();
    if (inputEntity == NULL)
    {
        printf("No Entity could be assigned for input!\n");
        return;
    }
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
    if (state[SDL_SCANCODE_W] && inputEntity->player1->rectangle->y > 0)
    {
        move_player_one_up();
    }
    if (state[SDL_SCANCODE_S] && (inputEntity->player1->rectangle->y + inputEntity->player1->rectangle->h) < WINDOW_HEIGHT)
    {
        move_player_one_down();
    }
    if (state[SDL_SCANCODE_O] && inputEntity->player2->rectangle->y > 0)
    {
        move_player_two_up();
    }
    if (state[SDL_SCANCODE_L] && (inputEntity->player2->rectangle->y + inputEntity->player2->rectangle->h) < WINDOW_HEIGHT)
    {
        move_player_two_down();
    }
}