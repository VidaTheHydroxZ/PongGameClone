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
static void ball_movement();
static void check_ball_walls_collision();
static void check_ball_player_collision();

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

static void ball_movement()
{
    // TODO: Ball movement around the screen
    entity->ball->rectangle->x += (entity->ball->speed_x * delta_time);
    entity->ball->rectangle->y += (entity->ball->speed_y * delta_time);
}

static void check_ball_walls_collision()
{
    if (entity->ball->rectangle->x <= 0 || (entity->ball->rectangle->x + entity->ball->rectangle->w) >= WINDOW_WIDTH)
    {
        entity->ball->speed_x *= -1;
    }
    else if (entity->ball->rectangle->y <= 0 || (entity->ball->rectangle->y + entity->ball->rectangle->h) >= WINDOW_HEIGHT)
    {
        entity->ball->speed_y *= -1;
    }
}

static void check_ball_player_collision()
{
    if  (entity->ball->rectangle->x < (entity->player1->rectangle->x + entity->player1->rectangle->w) &&
        (entity->ball->rectangle->x +  entity->ball->rectangle->w)   > entity->player1->rectangle->x  &&
         entity->ball->rectangle->y < (entity->player1->rectangle->y + entity->player1->rectangle->h) &&
        (entity->ball->rectangle->y +  entity->ball->rectangle->h)   > entity->player1->rectangle->y)
    {
        entity->ball->speed_x *= -1;

        entity->ball->rectangle->x = (entity->player1->rectangle->x + entity->player1->rectangle->w);
        printf("Ball collided with player 1!");
    }
    else if (entity->ball->rectangle->x < (entity->player2->rectangle->x + entity->player2->rectangle->w) &&
            (entity->ball->rectangle->x +  entity->ball->rectangle->w)   > entity->player2->rectangle->x  &&
             entity->ball->rectangle->y < (entity->player2->rectangle->y + entity->player2->rectangle->h) &&
            (entity->ball->rectangle->y +  entity->ball->rectangle->h)   > entity->player2->rectangle->y)
    {
        entity->ball->speed_x *= -1;

        entity->ball->rectangle->x = (entity->player2->rectangle->x - entity->ball->rectangle->w);
        printf("Ball collided with player 2!");
    }
}

static void move_player_one_up()
{
    entity->player1->rectangle->y -= 1000 * delta_time;
}

static void move_player_one_down()
{
    entity->player1->rectangle->y += 1000 * delta_time;
}

static void move_player_two_up()
{
    entity->player2->rectangle->y -= 1000 * delta_time;
}

static void move_player_two_down()
{
    entity->player2->rectangle->y += 1000 * delta_time;
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

    // Geta delta time factor converted to seconds to be used to update objects
    delta_time = (current_frame_time - last_frame_time) / 1000.0f;
    last_frame_time = current_frame_time;

    ball_movement();
    check_ball_player_collision();
    check_ball_walls_collision();
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
        move_player_one_up();
    }
    if (state[SDL_SCANCODE_S] && (entity->player1->rectangle->y + entity->player1->rectangle->h) < WINDOW_HEIGHT)
    {
        move_player_one_down();
    }
    if (state[SDL_SCANCODE_K] && entity->player2->rectangle->y > 0)
    {
        move_player_two_up();
    }
    if (state[SDL_SCANCODE_L] && (entity->player2->rectangle->y + entity->player2->rectangle->h) < WINDOW_HEIGHT)
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