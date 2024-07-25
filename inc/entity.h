#ifndef ENTITY_H
#define ENTITY_H

#include "SDL_rect.h"

typedef struct ball_s
{
    SDL_Rect* rectangle;
    float speed_x, speed_y;
} Ball;

typedef struct player_s
{
    SDL_Rect* rectangle;
} Player;


typedef struct entity_s
{
    Ball* ball;
    Player* player1;
    Player* player2;
} Entity;

void initialize_entities(Entity* entity);

#endif