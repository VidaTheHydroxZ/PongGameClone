#ifndef ENTITY_H
#define ENTITY_H

#include "SDL_rect.h"
#include "time.h"
#include "sound.h"

#include <stdbool.h>

typedef struct ball_s
{
    SDL_Rect* rectangle;
    Sound* ball_bounce_sound;
    int ball_bounce_sound_volume;
    float speed_x, speed_y, acceleration, max_speed;
} Ball;

typedef struct player_s
{
    SDL_Rect* rectangle;
    int player_score;
} Player;


typedef struct entity_s
{
    Ball* ball;
    Player* player1;
    Player* player2;
} Entity;

void initialize_entities();
void ball_movement();
void check_ball_walls_collision();
void check_ball_player_collision();
void move_player_one_up();
void move_player_one_down();
void move_player_two_up();
void move_player_two_down();
bool check_win_condition();
void free_all_entity_memory();
Entity* get_entity();

#endif