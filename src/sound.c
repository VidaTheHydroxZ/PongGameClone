#include "sound.h"
#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>

Mix_Chunk* sounds = NULL;
Mix_Music* music = NULL;

void init_mixer()
{
    int volume = 80;
    if(SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize audio! SDL Error: %s\n", SDL_GetError());
        return;
    }
    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_Mixer couldn't initialize. Error: %s\n", Mix_GetError());
        return;
    }
    set_volume(volume);
    load_music("vendor/sounds/game-music.mp3");
    play_music(volume, music);
}

void quit_mixer()
{
    Mix_FreeChunk(sounds);
    Mix_FreeMusic(music);
    Mix_Quit();
}

void load_music(const char* fileName)
{
    printf("Loading music file: %s\n", fileName);
    music = Mix_LoadMUS(fileName);
    if (music == NULL)
    {
        printf("Music loading failed!\n SDL_Mixer error: %s\n", Mix_GetError());
        return;
    }
}

Sound* load_sound(const char* fileName)
{
    printf("Loading sound file: %s\n", fileName);
    Sound* sound = malloc(sizeof(Sound));
    if (sound == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    sound->sound = Mix_LoadWAV(fileName);
    if (sound->sound == NULL)
    {
        printf("Sound loading failed!\n SDL_Mixer error: %s\n", Mix_GetError());
        free(sound);
        exit(1);
    }


    return sound;
}

void set_volume(int volume)
{
    volume = (MIX_MAX_VOLUME * volume) / 100;
}

void play_music(int volume, Mix_Music* music)
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_Volume(1, volume);
        Mix_PlayMusic(music, -1);
    }
}

void play_sound(int volume, Sound* sound)
{
    Mix_Volume(-1, volume);
    Mix_PlayChannel(-1, sound->sound, 0);
}