#pragma once

#include <SDL3/SDL.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "engine/button.h"

class MinesleeperCell : public Engine::Button
{
   public:
    MinesleeperCell(int x, int y, int w, int h, int row, int col);

    void handle_event(const SDL_Event& e) override;
    void render(SDL_Surface* surface) override;

    [[nodiscard]]
    int get_row() const
    {
        return row_;
    }

    [[nodiscard]]
    int get_col() const
    {
        return col_;
    }

   private:
    int row_;
    int col_;
};
