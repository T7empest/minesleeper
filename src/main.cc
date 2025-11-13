#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "engine/window.h"
#include "globals.h"
#include "minesleeper/ui.h"

int main(int, char**)
{
    SDL_Init(SDL_INIT_VIDEO);
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("SDL_Init");
#endif

    TTF_Init();
#ifdef SHOW_DEBUG_HELPERS
    Utils::CheckSDLError("TTF_Init");
#endif

    Engine::Window game_window;
    MinesleeperUI UI;

    SDL_Event event;
    bool should_quit{false};

    while (!should_quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                should_quit = true;
            }
            else
            {
                UI.handle_event(event);
            }
        }
        game_window.render();
        UI.render(game_window.get_surface());
        game_window.update();
    }

    TTF_Quit();
    SDL_Quit();
    return 0;
}
