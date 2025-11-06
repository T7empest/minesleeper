#pragma once

#define SHOW_DEBUG_HELPERS

#include <SDL3/SDL.h>

#include <iostream>
#include <string>

namespace UserEvents
{
}

namespace Config
{

// game settings
inline const std::string GAME_NAME{"Mine Sleeper"};

// size and positioning
inline constexpr int WINDOW_HEIGHT{200};
inline constexpr int WINDOW_WIDTH{400};

// colors
inline constexpr SDL_Color BACKGROUND_COLOR{170, 170, 170, 255};
inline constexpr SDL_Color BUTTON_COLOR{200, 200, 200, 255};
inline constexpr SDL_Color BUTTON_HOVER_COLOR{220, 220, 220, 255};

// asset path
inline const std::string BASE_PATH{SDL_GetBasePath()};
inline const std::string BOMB_IMAGE{BASE_PATH + "bomb.png"};
inline const std::string FLAG_IMAGE{BASE_PATH + "flag.png"};
inline const std::string FONT{BASE_PATH + "Roboto-Black.ttf"};

namespace Utils
{
#ifdef SHOW_DEBUG_HELPERS
inline void CheckSDLError(const std::string& msg)
{
    const char* error{SDL_GetError()};
    if (*error != '\0')
    {
        std::cerr << msg << " Error: " << error << std::endl;
    }
}
#endif
}  // namespace Utils
}  // namespace Config
