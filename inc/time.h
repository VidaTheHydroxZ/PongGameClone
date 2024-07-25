#ifndef TIME_H
#define TIME_H

typedef struct time_s
{
    float delta_time, last_frame_time, current_frame_time, frame_time;
} Time;

void initialize_time(Time* time);
void calculate_delta_time(Time* time);
void delay_frame(Time* time);
float get_delta_time(Time* time);

#endif