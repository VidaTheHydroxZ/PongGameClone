#include "entity.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

Entity* entity = NULL;

void initialize_entities()
{
    entity = (Entity*)malloc(sizeof(Entity));

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
    entity->ball->speed_x = 300.0f;
    entity->ball->speed_y = 300.0f;
    entity->ball->acceleration = 1.0001f;
    entity->ball->max_speed = 1100.0f;
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

void ball_movement()
{
    entity->ball->speed_x *= entity->ball->acceleration;
    entity->ball->speed_y *= entity->ball->acceleration;

    entity->ball->rectangle->x += (entity->ball->speed_x * 1.5f * get_delta_time());
    entity->ball->rectangle->y += (entity->ball->speed_y * 1.5f * get_delta_time());

    if (entity->ball->speed_x > entity->ball->max_speed) entity->ball->speed_x = entity->ball->max_speed;
    if (entity->ball->speed_y > entity->ball->max_speed) entity->ball->speed_y = entity->ball->max_speed;
}

void check_ball_walls_collision()
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

void check_ball_player_collision()
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

void move_player_one_up()
{
    entity->player1->rectangle->y -= 1000 * get_delta_time();
}

void move_player_one_down()
{
    entity->player1->rectangle->y += 1000 * get_delta_time();
}

void move_player_two_up()
{
    entity->player2->rectangle->y -= 1000 * get_delta_time();
}

void move_player_two_down()
{
    entity->player2->rectangle->y += 1000 * get_delta_time();
}

bool check_win_condition()
{
    if (entity->player1->player_score == 5 || entity->player2->player_score == 5)
    {
        printf("Game is over!\n");
        return true;
    }
    return false;
}

void free_all_entity_memory()
{
    free(entity->ball->rectangle);
    free(entity->player1->rectangle);
    free(entity->player2->rectangle);

    free(entity->ball);
    free(entity->player1);
    free(entity->player2);
    
    free(entity);
}

Entity* get_entity()
{
    Entity* newEntity = malloc(sizeof(Entity));
    newEntity = entity;
    if (newEntity == NULL)
    {
        printf("No Entity assigned can be returned!\n");
    }
    return newEntity;
}