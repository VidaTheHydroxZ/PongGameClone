#include "time.h"
#include "utils.h"
#include "SDL_timer.h"

void initialize_time(Time* time)
{
    time->current_frame_time = 0.0f;
    time->delta_time = 0.0f;
    time->frame_time = 0.0f;
    time->last_frame_time = 0.0f;
}


float get_delta_time(Time* time)
{
    return time->delta_time;
}

void calculate_delta_time(Time* time)
{
    time->current_frame_time = SDL_GetTicks();

    // Geta delta time factor converted to seconds to be used to update objects
    time->delta_time = (time->current_frame_time - time->last_frame_time) / 1000.0f;
    time->last_frame_time = time->current_frame_time;
}

void delay_frame(Time* time)
{
    time->frame_time = SDL_GetTicks() - time->last_frame_time;

    if (FRAME_TARGET_TIME > time->frame_time)
    {
        SDL_Delay(FRAME_TARGET_TIME - time->frame_time);
    }
}