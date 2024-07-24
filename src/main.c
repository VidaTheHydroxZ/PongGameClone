#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "entity.h"
#include "SDL.h"

int32_t game_is_running;
SDL_Window* window;
SDL_Renderer* renderer;
Entity* entity;
float delta_time;

float last_frame_time = 0.0f;

static void move_player_down();
static void move_player_up();
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

static void move_player_down()
{
    entity->ball->rectangle->y += 200 * delta_time;
}

static void move_player_up()
{
    entity->ball->rectangle->y -= 200 * delta_time;
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            game_is_running = 0;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            game_is_running = 0;
            else if (event.key.keysym.sym == SDLK_DOWN) // Ako je tipka DOLJE pritisnuta, pomakni igraca DOLJE
            {
                move_player_down();
            }
            else if (event.key.keysym.sym == SDLK_UP) // Ako je tipka GORE pritisnuta, pomakni igraca GORE
            {
                move_player_up();
            }
            break;
    }
}

void update()
{
    // Geta delta time factor converted to seconds to be used to update my objects later
    delta_time = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks64();
}

void setup()
{
    entity = (Entity*)malloc(sizeof(Entity));
    initialize_entities(entity);
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO: Draw a rectangle

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, entity->ball->rectangle);
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
        process_input();
        update();
        render();
    }

    destroy_window();
    free_memory();

    return 0;
}