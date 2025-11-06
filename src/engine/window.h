#pragma once

#include "SDL3/SDL.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include "globals.h"

namespace Engine
{

class Window
{
   public:
    Window()
    {
        sdl_window_ =
            SDL_CreateWindow(Config::GAME_NAME.c_str(), Config::WINDOW_WIDTH,
                             Config::WINDOW_HEIGHT, 0);
    }

    ~Window()
    {
        if (sdl_window_ && SDL_WasInit(SDL_INIT_VIDEO))
        {
            SDL_DestroyWindow(sdl_window_);
        }
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void render()
    {
        const auto* fmt{SDL_GetPixelFormatDetails(get_surface()->format)};
        SDL_FillSurfaceRect(
            get_surface(), nullptr,
            SDL_MapRGB(fmt, nullptr, Config::BACKGROUND_COLOR.r,
                       Config::BACKGROUND_COLOR.g, Config::BACKGROUND_COLOR.b));
    }

    void update() { SDL_UpdateWindowSurface(sdl_window_); }

    SDL_Surface* get_surface() const
    {
        return SDL_GetWindowSurface(sdl_window_);
    }

   private:
    SDL_Window* sdl_window_{nullptr};
};

}  // namespace Engine
