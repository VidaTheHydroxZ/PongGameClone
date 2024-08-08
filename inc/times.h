#ifndef TIMES_H
#define TIMES_H

typedef struct time_s
{
    float delta_time, last_frame_time, current_frame_time, frame_time;
} Time;

void initialize_time();
void calculate_delta_time();
void delay_frame();
float get_delta_time();
void free_time_memory();

#endif