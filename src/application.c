#include "application.h"
#include "utils.h"
#include "time.h"
#include "entity.h"
#include "input.h"
#include "sound.h"
#include "renderer.h"
#include "text.h"
#include "SDL.h"
#include "SDL_ttf.h"

static void free_memory();
static void quit_game();

void update()
{
    calculate_delta_time();
    delay_frame();
    ball_movement();
    check_ball_player_collision();
    check_ball_walls_collision();
    if(check_win_condition()) quit_game();
}

void init()
{
    game_is_running = initialize_window();
    if (game_is_running != INIT_SUCCESS)
    {
        exit(1);
    }
    init_mixer();
    initialize_entities();
    initialize_time();
    initialize_text();
    get_entity_for_input();
    get_entity_for_renderer();
}

static void free_memory()
{
    free_all_entity_memory();
    free_text_memory();
    free_time_memory();
    quit_mixer();
}

static void quit_game()
{
    free_memory();
    TTF_Quit();
    destroy_window();
    game_is_running = 0;
}