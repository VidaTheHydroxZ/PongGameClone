#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "SDL.h"

int32_t game_is_running;
SDL_Window* window;
SDL_Renderer* renderer;
float delta_time;

float last_frame_time = 0.0f;

struct ball 
{
    float x, y, width, height;
} ball;

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
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                move_player_down();
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                move_player_up();
            }
            break;
    }
}

void move_player_down()
{
    ball.y += 50 * delta_time;
}

void move_player_up()
{
    ball.y -= 50 * delta_time;
}

void check_for_player_movement();

void update()
{
    // Geta delta time factor converted to seconds to be used to update my objects later
    delta_time = (SDL_GetTicks64() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks64();
    check_for_player_movement();
}

void setup()
{
    ball.x = 20.0f;
    ball.y = 20.0f;
    ball.width = 15.0f;
    ball.height = 100.0f;
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // TODO: Draw a rectangle
    SDL_Rect ball_rect = {(int)ball.x, (int)ball.y, (int)ball.width, (int)ball.height};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball_rect);
    // Present the screen
    SDL_RenderPresent(renderer);
}

void destroy_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    return 0;
}