#include "entity.h"
#include "utils.h"

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

void ball_movement(Entity* ball, Time* time)
{
    ball->ball->rectangle->x += (ball->ball->speed_x * get_delta_time(time));
    ball->ball->rectangle->y += (ball->ball->speed_y * get_delta_time(time));
}

void check_ball_walls_collision(Entity* ball)
{
    if (ball->ball->rectangle->x <= 0 || (ball->ball->rectangle->x + ball->ball->rectangle->w) >= WINDOW_WIDTH)
    {
        ball->ball->speed_x *= -1;
    }
    else if (ball->ball->rectangle->y <= 0 || (ball->ball->rectangle->y + ball->ball->rectangle->h) >= WINDOW_HEIGHT)
    {
        ball->ball->speed_y *= -1;
    }
}

void check_ball_player_collision(Entity* ball)
{
    if  (ball->ball->rectangle->x < (ball->player1->rectangle->x + ball->player1->rectangle->w) &&
        (ball->ball->rectangle->x +  ball->ball->rectangle->w)   > ball->player1->rectangle->x  &&
         ball->ball->rectangle->y < (ball->player1->rectangle->y + ball->player1->rectangle->h) &&
        (ball->ball->rectangle->y +  ball->ball->rectangle->h)   > ball->player1->rectangle->y)
    {
        ball->ball->speed_x *= -1;

        ball->ball->rectangle->x = (ball->player1->rectangle->x + ball->player1->rectangle->w);
    }
    else if (ball->ball->rectangle->x < (ball->player2->rectangle->x + ball->player2->rectangle->w) &&
            (ball->ball->rectangle->x +  ball->ball->rectangle->w)   > ball->player2->rectangle->x  &&
             ball->ball->rectangle->y < (ball->player2->rectangle->y + ball->player2->rectangle->h) &&
            (ball->ball->rectangle->y +  ball->ball->rectangle->h)   > ball->player2->rectangle->y)
    {
        ball->ball->speed_x *= -1;

        ball->ball->rectangle->x = (ball->player2->rectangle->x - ball->ball->rectangle->w);
    }
}

void move_player_one_up(Entity* player, Time* time)
{
    player->player1->rectangle->y -= 1000 * get_delta_time(time);
}

void move_player_one_down(Entity* player, Time* time)
{
    player->player1->rectangle->y += 1000 * get_delta_time(time);
}

void move_player_two_up(Entity* player, Time* time)
{
    player->player2->rectangle->y -= 1000 * get_delta_time(time);
}

void move_player_two_down(Entity* player, Time* time)
{
    player->player2->rectangle->y += 1000 * get_delta_time(time);
}