#ifndef SOUND_H
#define SOUND_H

#include "SDL_mixer.h"

typedef struct sound_s
{
    Mix_Chunk* sound;
} Sound;

void play_sound(int volume, Sound* sound);
void play_music(int volume, Mix_Music* music);

Sound* load_sound(const char* fileName);
void load_music(const char* fileName);

void set_volume(int volume);

void init_mixer();
void quit_mixer();

#endif