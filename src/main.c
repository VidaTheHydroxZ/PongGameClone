#include "application.h"
#include "renderer.h"
#include "entity.h"
#include "input.h"

int SDL_main (int argc, char* argv[])
{
    init();
    while(game_is_running)
    {
        update();
        process_input();
        render();
        if(check_win_condition()) quit_game();
    }
    return 0;
}