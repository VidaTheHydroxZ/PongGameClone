#ifndef ENTITY_H
#define ENTITY_H

#include "SDL_rect.h"
#include "time.h"

typedef struct ball_s
{
    SDL_Rect* rectangle;
    float speed_x, speed_y;
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

void initialize_entities(Entity* entity);
void ball_movement(Entity* ball, Time* time);
void check_ball_walls_collision(Entity* ball);
void check_ball_player_collision(Entity* ball);
void move_player_one_up(Entity* player, Time* time);
void move_player_one_down(Entity* player, Time* time);
void move_player_two_up(Entity* player, Time* time);
void move_player_two_down(Entity* player, Time* time);

#endif