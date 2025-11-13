#pragma once

#include <SDL3/SDL.h>

#include "globals.h"
#include "minesleeper/grid.h"

class MinesleeperUI
{
   public:
    void render(SDL_Surface* surface) { grid.render(surface); }
    void handle_event(const SDL_Event& e) { grid.handle_event(e); }

   private:
    MinesleeperGrid grid{Config::PADDING, Config::PADDING};
};
