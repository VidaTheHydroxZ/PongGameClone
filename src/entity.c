#include "entity.h"

#include <stdlib.h>

void initialize_entities(Entity* entity)
{
    entity->ball = (Ball*)malloc(sizeof(Ball));
    entity->player1 = (Player*)malloc(sizeof(Player));
    entity->player2 = (Player*)malloc(sizeof(Player));

    entity->ball->rectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    entity->player1->rectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    entity->player2->rectangle = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    entity->ball->rectangle->x = 950.0f;
    entity->ball->rectangle->y = 20.0f;
    entity->ball->rectangle->h = 20.0f;
    entity->ball->rectangle->w = 20.0f;
    entity->ball->speed_x = 500.0f;
    entity->ball->speed_y = 500.0f;

    entity->player1->rectangle->x = 50.f;
    entity->player1->rectangle->y = 540.0f;
    entity->player1->rectangle->h = 100.0f;
    entity->player1->rectangle->w = 20.0f;

    entity->player2->rectangle->x = 1850.0f;
    entity->player2->rectangle->y = 540.0f;
    entity->player2->rectangle->h = 100.0f;
    entity->player2->rectangle->w = 20.0f;
}