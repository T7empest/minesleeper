#pragma once

#include <SDL3/SDL.h>

#include <memory>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "engine/button.h"
#include "engine/image.h"
#include "engine/text.h"

class MinesleeperCell : public Engine::Button
{
   public:
    MinesleeperCell(int x, int y, int w, int h, int row, int col);

    void handle_event(const SDL_Event& e) override;
    void render(SDL_Surface* surface) override;

    bool place_bomb();

    [[nodiscard]]
    bool get_has_bomb() const
    {
        return has_bomb;
    }

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

   protected:
    void handle_left_click() override;

   private:
    void handle_bomb_placed(const SDL_UserEvent& e);
    void handle_cell_cleared(const SDL_UserEvent& e);
    bool is_adjacent(const MinesleeperCell* other) const;
    void report_event(uint32_t event_type);
    void clear_cell();

    bool is_cleared{false};
    bool has_bomb{false};
    int row_;
    int col_;
    int adjacent_bombs_{0};
    std::unique_ptr<Engine::Image> bomb_image_;
    std::unique_ptr<Engine::Text> text_;
};
