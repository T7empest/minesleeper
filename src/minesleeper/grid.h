#pragma once

#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "cell.h"
#include "globals.h"
class MinesleeperGrid
{
   public:
    MinesleeperGrid(int x, int y)
    {
        using namespace Config;
        children.reserve(GRID_COLUMNS * GRID_ROWS);
        for (int col{1}; col <= GRID_COLUMNS; ++col)
        {
            for (int row{1}; row <= GRID_ROWS; ++row)
            {
                constexpr int spacing{CELL_SIZE + PADDING};
                children.emplace_back(x + (spacing) * (col - 1),
                                      y + (spacing) * (row - 1), CELL_SIZE,
                                      CELL_SIZE, row, col);
            }
        }
    }

    void render(SDL_Surface* surface)
    {
        for (auto& child : children)
        {
            child.render(surface);
        }
    }

    void handle_event(const SDL_Event& e)
    {
        for (auto& child : children)
        {
            child.handle_event(e);
        }
    }

    std::vector<MinesleeperCell> children;
};
