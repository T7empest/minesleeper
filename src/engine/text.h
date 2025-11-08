#pragma once

#include <string>

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "globals.h"
namespace Engine
{
class Text
{
   public:
    Text(int x, int y, int w, int h, const std::string& content,
         SDL_Color color = {0, 0, 0, 255}, float font_size = 30.0f)
        : destination_rect_(x, y, w, h), color_{color}
    {
        font_ = TTF_OpenFont(Config::FONT.c_str(), font_size);
#ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLError("TTF_OpenFont");
#endif
        set_text(content);
    }
    ~Text()
    {
        if (TTF_WasInit())
        {
            TTF_CloseFont(font_);
        }
        if (text_surface_)
        {
            SDL_DestroySurface(text_surface_);
        }
    }
    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

    void set_text(const std::string& text) { set_text(text, color_); }

    void set_text(const std::string& text, SDL_Color new_color)
    {
        if (text_surface_)
        {
            SDL_DestroySurface(text_surface_);
        }
        color_ = new_color;

        text_surface_ = TTF_RenderText_Blended(font_, text.c_str(), 0, color_);

        auto [x, y, w, h] = destination_rect_;
        // horizontal centering
        const int width_diff{w - text_surface_->w};
        const int left_offset{width_diff / 2};

        // vertical centering
        const int height_diff{h - text_surface_->h};
        const int top_offset{height_diff / 2};

        text_position_ = {x + left_offset, y + top_offset, text_surface_->w,
                          text_surface_->h};
    }

    void render(SDL_Surface* surface)
    {
        SDL_BlitSurface(text_surface_, nullptr, surface, &text_position_);
    }

   private:
    SDL_Surface* text_surface_{nullptr};
    TTF_Font* font_{nullptr};
    SDL_Rect destination_rect_{0, 0, 0, 0};
    SDL_Rect text_position_{0, 0, 0, 0};
    SDL_Color color_{0, 0, 0, 255};
};
}  // namespace Engine
