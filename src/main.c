#include "application.h"
#include "renderer.h"
#include "entity.h"
#include "input.h"

int SDL_main (int argc, char* argv[])
{
    init();
    while(game_is_running)
    {
        render();
        process_input();
        update();
    }
    return 0;
}