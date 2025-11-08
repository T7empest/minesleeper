#pragma once

#include <string>

#include "SDL3/SDL.h"
#include "globals.h"

namespace Engine
{
class Image
{
   public:
    Image(int x, int y, int w, int h, const std::string& filename,
          int padding = 12)
        : destination_{x + padding / 2, y + padding / 2, w - padding,
                       h - padding}
    {
        image_surface_ = IMG_Load(filename.c_str());
#ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLError("IMG_Load");
#endif
    }
    ~Image()
    {
        if (image_surface_)
        {
            SDL_DestroySurface(image_surface_);
        }
    }
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    void render(SDL_Surface* surface)
    {
        SDL_BlitSurfaceScaled(image_surface_, nullptr, surface, &destination,
                              SDL_SCALEMODE_LINEAR);
    }

   private:
    SDL_Surface* image_surface_{nullptr};
    SDL_Rect destination_{0, 0, 0, 0};
};
}  // namespace Engine
