#pragma once

#include <SDL3/SDL.h>

#include "SDL3/SDL_events.h"
#include "globals.h"
#include "rectangle.h"

namespace Engine
{
class Button : public Rectangle
{
   public:
    Button(int x, int y, int w, int h) : Rectangle{x, y, w, h}
    {
        set_color(Config::BUTTON_COLOR);
    }

    virtual void handle_event(const SDL_Event& e)
    {
        if (is_disabled_) return;
        if (e.type == SDL_EVENT_MOUSE_MOTION)
        {
            handle_mouse_motion(e.motion);
        }
        else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (is_within_bounds((int)e.button.x, (int)e.button.y))
            {
                e.button.button == SDL_BUTTON_LEFT ? handle_left_click()
                                                   : handle_right_click();
            }
        }
    }

    void set_is_disabled(bool new_value) { is_disabled_ = new_value; }

   protected:
    virtual void handle_left_click();
    virtual void handle_right_click();
    virtual void handle_mouse_motion(const SDL_MouseMotionEvent& e)
    {
        if (is_within_bounds((int)e.x, (int)e.y))
        {
            set_color(Config::BUTTON_HOVER_COLOR);
        }
        else
        {
            set_color(Config::BUTTON_COLOR);
        }
    }

   private:
    bool is_disabled_{false};
};
}  // namespace Engine
