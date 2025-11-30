#pragma once

#include <cstddef>
#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "cell.h"
#include "engine/random.h"
#include "globals.h"

class MinesleeperGrid
{
   public:
    MinesleeperGrid(int x, int y)
    {
        using namespace Config;
        children_.reserve(GRID_COLUMNS * GRID_ROWS);
        for (int col{1}; col <= GRID_COLUMNS; ++col)
        {
            for (int row{1}; row <= GRID_ROWS; ++row)
            {
                constexpr int spacing{CELL_SIZE + PADDING};
                children_.emplace_back(x + (spacing) * (col - 1),
                                       y + (spacing) * (row - 1), CELL_SIZE,
                                       CELL_SIZE, row, col);
            }
        }
        place_bombs();
    }

    void render(SDL_Surface* surface)
    {
        for (auto& child : children_)
        {
            child.render(surface);
        }
    }

    void handle_event(const SDL_Event& e)
    {
        if (e.type == UserEvents::CELL_CLEARED)
        {
            handle_cell_cleared(e.user);
        }
        else if (e.type == UserEvents::NEW_GAME)
        {
            for (auto& child : children_)
            {
                child.reset();
            }
            place_bombs();
        }
        for (auto& child : children_)
        {
            child.handle_event(e);
        }
    }

   private:
    void place_bombs()
    {
        int bombs_to_place{Config::BOMB_COUNT};
        cells_to_clear_ =
            Config::GRID_COLUMNS * Config::GRID_ROWS - Config::BOMB_COUNT;
        while (bombs_to_place > 0)
        {
            const size_t random_idx{
                Engine::Random::Int(0, children_.size() - 1)};
            if (children_[random_idx].place_bomb())
            {
                --bombs_to_place;
            }
        }
    }

    void handle_cell_cleared(const SDL_UserEvent& e)
    {
        auto* cell{static_cast<MinesleeperCell*>(e.data1)};

        if (cell->get_has_bomb())
        {
            SDL_Event event{};
            event.type = UserEvents::GAME_LOST;
            SDL_PushEvent(&event);
        }
        else
        {
            --cells_to_clear_;
            if (cells_to_clear_ == 0)
            {
                SDL_Event event{};
                event.type = UserEvents::GAME_WON;
                SDL_PushEvent(&event);
            }
        }
    }

    std::vector<MinesleeperCell> children_;
    int cells_to_clear_{0};
};
