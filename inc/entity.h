#ifndef ENTITY_H
#define ENTITY_H

#include "SDL_rect.h"

typedef struct ball_m
{
    SDL_Rect* rectangle;
} Ball;

typedef struct player_m
{
    SDL_Rect* rectangle;
} Player;


typedef struct entity_m 
{
    Ball* ball;
    Player* player1;
    Player* player2;
} Entity;

void initialize_entities(Entity* entity);

#endif