#pragma once

#include "SDL3/SDL.h"

namespace Engine
{
class Rectangle
{
   public:
    Rectangle(int x, int y, int w, int h, SDL_Color color = {0, 0, 0, 255})
        : rect_{x, y, w, h}, color_(color)
    {
    }

    virtual void render(SDL_Surface* surface)
    {
        const auto* fmt = SDL_GetPixelFormatDetails(surface->format);
        SDL_FillSurfaceRect(
            surface, &rect_,
            SDL_MapRGB(fmt, nullptr, color_.r, color_.g, color_.b));
    }

    void set_color(SDL_Color c) { color_ = c; }

    bool is_within_bounds(int x, int y) const
    {
        if (x < rect_.x) return false;
        if (x > rect_.x + rect_.w) return false;
        if (y < rect_.y) return false;
        if (y > rect_.y + rect_.h) return false;
        return true;
    }

    const SDL_Rect* get_rect() const { return &rect_; }

    virtual ~Rectangle() = default;

   private:
    SDL_Rect rect_{0, 0, 0, 0};
    SDL_Color color_{0, 0, 0, 0};
};
}  // namespace Engine
