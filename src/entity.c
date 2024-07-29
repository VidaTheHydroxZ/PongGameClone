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
    entity->ball->acceleration = 1.0001f;
    entity->ball->max_speed = 900.0f;
    entity->ball->ball_bounce_sound_volume = 80;
    entity->ball->ball_bounce_sound = load_sound("vendor/sounds/ball-bounce-sound.wav");

    entity->player1->rectangle->x = 50.f;
    entity->player1->rectangle->y = 540.0f;
    entity->player1->rectangle->h = 100.0f;
    entity->player1->rectangle->w = 20.0f;
    entity->player1->player_score = 0;

    entity->player2->rectangle->x = 1850.0f;
    entity->player2->rectangle->y = 540.0f;
    entity->player2->rectangle->h = 100.0f;
    entity->player2->rectangle->w = 20.0f;
    entity->player2->player_score = 0;
}

void ball_movement(Entity* entity, Time* time)
{
    entity->ball->speed_x *= entity->ball->acceleration;
    entity->ball->speed_y *= entity->ball->acceleration;

    entity->ball->rectangle->x += (entity->ball->speed_x * 1.5f * get_delta_time(time));
    entity->ball->rectangle->y += (entity->ball->speed_y * 1.5f * get_delta_time(time));

    if (entity->ball->speed_x > entity->ball->max_speed) entity->ball->speed_x = entity->ball->max_speed;
    if (entity->ball->speed_y > entity->ball->max_speed) entity->ball->speed_y = entity->ball->max_speed;
}

void check_ball_walls_collision(Entity* entity)
{
    if(entity)
    {
        if (entity->ball->rectangle->x <= 0)
        {
            entity->ball->speed_x *= -1;
            entity->player2->player_score++;

            play_sound(entity->ball->ball_bounce_sound_volume, entity->ball->ball_bounce_sound);
        }
        else if ((entity->ball->rectangle->x + entity->ball->rectangle->w)  >= WINDOW_WIDTH)
        {
            entity->ball->speed_x *= -1;
            entity->player1->player_score++;

            play_sound(entity->ball->ball_bounce_sound_volume, entity->ball->ball_bounce_sound);
        }
        else if (entity->ball->rectangle->y <= 0 || (entity->ball->rectangle->y + entity->ball->rectangle->h) >= WINDOW_HEIGHT)
        {
            entity->ball->speed_y *= -1;

            play_sound(entity->ball->ball_bounce_sound_volume, entity->ball->ball_bounce_sound);
        }
    }
}

void check_ball_player_collision(Entity* entity)
{
    if(entity)
    {
        if  (entity->ball->rectangle->x < (entity->player1->rectangle->x + entity->player1->rectangle->w) &&
            (entity->ball->rectangle->x +  entity->ball->rectangle->w)   > entity->player1->rectangle->x  &&
             entity->ball->rectangle->y < (entity->player1->rectangle->y + entity->player1->rectangle->h) &&
            (entity->ball->rectangle->y +  entity->ball->rectangle->h)   > entity->player1->rectangle->y)
        {
            entity->ball->speed_x *= -1;

            entity->ball->rectangle->x = (entity->player1->rectangle->x + entity->player1->rectangle->w);

            play_sound(entity->ball->ball_bounce_sound_volume, entity->ball->ball_bounce_sound);
        }
        else if (entity->ball->rectangle->x < (entity->player2->rectangle->x + entity->player2->rectangle->w) &&
                (entity->ball->rectangle->x +  entity->ball->rectangle->w)   > entity->player2->rectangle->x  &&
                 entity->ball->rectangle->y < (entity->player2->rectangle->y + entity->player2->rectangle->h) &&
                (entity->ball->rectangle->y +  entity->ball->rectangle->h)   > entity->player2->rectangle->y)
        {
            entity->ball->speed_x *= -1;

            entity->ball->rectangle->x = (entity->player2->rectangle->x - entity->ball->rectangle->w);

            play_sound(entity->ball->ball_bounce_sound_volume, entity->ball->ball_bounce_sound);
        }
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