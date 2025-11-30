#pragma once
#include <SDL3/SDL.h>

#include <memory>
#include <string>

#include "SDL3/SDL_surface.h"
#include "engine/image.h"
#include "engine/rectangle.h"
#include "engine/text.h"
#include "globals.h"

class FlagCounter : public Engine::Rectangle
{
   public:
    FlagCounter(int x, int y, int w, int h)
        : Rectangle{x, y, w, h, Config::FLAG_COUNTER_COLOR},
          image_{std::make_unique<Engine::Image>(
              x, y, Config::FOOTER_HEIGHT - Config::PADDING,
              Config::FOOTER_HEIGHT - Config::PADDING, Config::FLAG_IMAGE, 24)},
          text_{std::make_unique<Engine::Text>(
              x + Config::FOOTER_HEIGHT, y, w - Config::FOOTER_HEIGHT - 24, h,
              std::to_string(Config::BOMB_COUNT), SDL_Color{255, 255, 255, 255},
              20.0f)}
    {
    }

    void render(SDL_Surface* surface) override
    {
        Rectangle::render(surface);
        text_->render(surface);
        image_->render(surface);
    }

    void handle_event(const SDL_Event& e)
    {
        if (e.type == UserEvents::FLAG_PLACED)
        {
            --flags_available_;
        }
        else if (e.type == UserEvents::FLAG_CLEARED)
        {
            ++flags_available_;
        }
        else if (e.type == UserEvents::GAME_WON)
        {
            flags_available_ = 0;
        }
        else if (e.type == UserEvents::NEW_GAME)
        {
            flags_available_ = Config::BOMB_COUNT;
        }
        else
        {
            return;
        }
        text_->set_text(std::to_string(flags_available_));
    }

   private:
    std::unique_ptr<Engine::Image> image_;
    std::unique_ptr<Engine::Text> text_;
    int flags_available_{Config::BOMB_COUNT};
};
