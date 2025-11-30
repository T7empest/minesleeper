#include "minesleeper/cell.h"

#include <iostream>
#include <memory>
#include <string>

#include "SDL3/SDL_events.h"
#include "engine/button.h"
#include "engine/image.h"
#include "globals.h"

MinesleeperCell::MinesleeperCell(int x, int y, int w, int h, int row, int col)
    : Button{x, y, w, h}, row_{row}, col_{col}
{
    bomb_image_ =
        std::make_unique<Engine::Image>(x, y, w, h, Config::BOMB_IMAGE);
    flag_image_ =
        std::make_unique<Engine::Image>(x, y, w, h, Config::FLAG_IMAGE);
    text_ = std::make_unique<Engine::Text>(
        x, y, w, h, std::to_string(adjacent_bombs_),
        Config::TEXT_COLORS[adjacent_bombs_]);
}

void MinesleeperCell::handle_event(const SDL_Event& e)
{
    if (e.type == UserEvents::CELL_CLEARED)
    {
        handle_cell_cleared(e.user);
    }
    else if (e.type == UserEvents::BOMB_PLACED)
    {
        handle_bomb_placed(e.user);
    }
    else if (e.type == UserEvents::GAME_WON)
    {
        if (has_bomb_)
        {
            has_flag_ = true;
            set_color(Config::BUTTON_SUCCESS_COLOR);
        }
        set_is_disabled(true);
    }
    else if (e.type == UserEvents::GAME_LOST)
    {
        if (has_bomb_)
        {
            is_cleared_ = true;
            set_color(Config::BUTTON_FAILURE_COLOR);
        }
        set_is_disabled(true);
    }
    Button::handle_event(e);
}

void MinesleeperCell::render(SDL_Surface* surface)
{
    Button::render(surface);
    if (has_flag_)
    {
        flag_image_->render(surface);
    }
    if (is_cleared_ && has_bomb_)
    {
        bomb_image_->render(surface);
        std::cout << Config::BOMB_IMAGE.c_str() << std::endl;
    }
    else if (is_cleared_ && adjacent_bombs_ > 0)
    {
        text_->render(surface);
    }
#ifdef SHOW_DEBUG_HELPERS
    else if (has_bomb)
    {
        bomb_image_->render(surface);
    }
#endif
}

void MinesleeperCell::clear_cell()
{
    if (is_cleared_) return;
    is_cleared_ = true;
    set_is_disabled(true);
    set_color(Config::BUTTON_CLEARED_COLOR);
    report_event(UserEvents::CELL_CLEARED);
}

void MinesleeperCell::handle_left_click()
{
    if (!has_flag_) clear_cell();
}

void MinesleeperCell::report_event(uint32_t event_type)
{
    SDL_Event event{};
    event.type = event_type;
    event.user.data1 = this;
    SDL_PushEvent(&event);
}

bool MinesleeperCell::place_bomb()
{
    if (has_bomb_) return false;
    has_bomb_ = true;
    report_event(UserEvents::BOMB_PLACED);
    return true;
}

bool MinesleeperCell::is_adjacent(const MinesleeperCell* other) const
{
    return !(other == this) && std::abs(get_row() - other->get_row()) <= 1 &&
           std::abs(get_col() - other->get_col()) <= 1;
}

void MinesleeperCell::handle_bomb_placed(const SDL_UserEvent& e)
{
    const auto* cell{static_cast<MinesleeperCell*>(e.data1)};
    if (is_adjacent(cell))
    {
        ++adjacent_bombs_;
        text_->set_text(std::to_string(adjacent_bombs_),
                        Config::TEXT_COLORS[adjacent_bombs_]);
    }
}

void MinesleeperCell::handle_cell_cleared(const SDL_UserEvent& e)
{
    // get the cell that was just cleared
    const auto* cell{static_cast<MinesleeperCell*>(e.data1)};

    // if has bomb -> nothing
    if (cell->has_bomb_) return;

    // If the cell is adjacent to this cell and
    // if it had no adjacent bombs, we should
    // clear this cell too
    if (is_adjacent(cell) && cell->adjacent_bombs_ == 0)
    {
        clear_cell();
    }
}

void MinesleeperCell::reset()
{
    is_cleared_ = false;
    has_bomb_ = false;
    has_flag_ = false;
    adjacent_bombs_ = 0;
    set_is_disabled(false);
    set_color(Config::BUTTON_COLOR);
    text_->set_text(std::to_string(adjacent_bombs_),
                    Config::TEXT_COLORS[adjacent_bombs_]);
}

void MinesleeperCell::handle_right_click()
{
    if (has_flag_)
    {
        report_event(UserEvents::FLAG_CLEARED);
        has_flag_ = false;
    }
    else
    {
        report_event(UserEvents::FLAG_PLACED);
        has_flag_ = true;
    }
}
