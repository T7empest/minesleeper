#pragma once
#include <SDL3/SDL.h>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include "engine/button.h"
#include "engine/text.h"
#include "globals.h"

class NewGameButton : public Engine::Button
{
   public:
    NewGameButton(int x, int y, int w, int h)
        : Button{x, y, w, h}, text_{x, y, w, h, "NEW GAME", {}, 20.0f}
    {
    }

    void render(SDL_Surface* surface)
    {
        Button::render(surface);
        text_.render(surface);
    }

   protected:
    void handle_left_click() override
    {
        SDL_Event e{};
        e.type = UserEvents::NEW_GAME;
        SDL_PushEvent(e);
    }

   private:
    Engine::Text text_;
};
