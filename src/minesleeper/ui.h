#pragma once

#include <SDL3/SDL.h>

#include "globals.h"
#include "minesleeper/flag_counter.h"
#include "minesleeper/grid.h"
#include "minesleeper/new_game_button.h"

class MinesleeperUI
{
   public:
    void render(SDL_Surface* surface)
    {
        grid_.render(surface);
        button_.render(surface);
        counter_.render(surface);
    }
    void handle_event(const SDL_Event& e)
    {
        grid_.handle_event(e);
        button_.handle_event(e);
        counter_.handle_event(e);
    }

   private:
    MinesleeperGrid grid_{Config::PADDING, Config::PADDING};
    NewGameButton button_{Config::PADDING,
                          Config::GRID_HEIGHT + Config::PADDING * 2,
                          Config::WINDOW_HEIGHT - Config::PADDING * 3 -
                              Config::FLAG_COUNTER_WIDTH,
                          Config::FOOTER_HEIGHT - Config::PADDING};
    FlagCounter counter_{
        Config::WINDOW_WIDTH - Config::PADDING - Config::FLAG_COUNTER_WIDTH,
        Config::GRID_HEIGHT + Config::PADDING * 2, Config::FLAG_COUNTER_WIDTH,
        Config::FOOTER_HEIGHT - Config::PADDING};
};
