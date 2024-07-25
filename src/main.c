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

float delta_time = 0.0f;
float last_frame_time = 0.0f;
float current_frame_time = 0.0f;
float frame_time = 0.0f;

static void move_player_one_down();
static void move_player_one_up();
static void move_player_two_down();
static void move_player_two_up();
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

static void move_player_one_down()
{
    entity->player1->rectangle->y += 1000 * delta_time;
}

static void move_player_one_up()
{
    entity->player1->rectangle->y -= 1000 * delta_time;
}

static void move_player_two_down()
{
    entity->player2->rectangle->y += 1000 * delta_time;
}

static void move_player_two_up()
{
    entity->player2->rectangle->y -= 1000 * delta_time;
}

void delay_frame()
{
    frame_time = SDL_GetTicks() - last_frame_time;

    if (FRAME_TARGET_TIME > frame_time)
    {
        SDL_Delay(FRAME_TARGET_TIME - frame_time);
    }
}

void update()
{
    current_frame_time = SDL_GetTicks();
    // Geta delta time factor converted to seconds to be used to update my objects later
    delta_time = (current_frame_time - last_frame_time) / 1000.0f;
    last_frame_time = current_frame_time;
}

void process_input()
{
    SDL_Event event;
    SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_Quit)
        {
            game_is_running = 0;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_ESCAPE])
    {
        game_is_running = 0;
    }
    if (state[SDL_SCANCODE_W])
    {
        move_player_one_up();
    }
    if (state[SDL_SCANCODE_S])
    {
        move_player_one_down();
    }
    if (state[SDL_SCANCODE_K])
    {
        move_player_two_up();
    }
    if (state[SDL_SCANCODE_L])
    {
        move_player_two_down();
    }
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
        delay_frame();
    }

    free_memory();
    destroy_window();
    
    return 0;
}