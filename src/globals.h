#pragma once

#include "SDL3/SDL_error.h"
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
inline constexpr int GRID_COLUMNS{8};
inline constexpr int GRID_ROWS{4};

// size and positioning
inline constexpr int PADDING{5};
inline constexpr int CELL_SIZE{50};
inline constexpr int GRID_HEIGHT{CELL_SIZE * GRID_ROWS +
                                 PADDING * (GRID_ROWS - 1)};
inline constexpr int GRID_WIDTH{CELL_SIZE * GRID_COLUMNS +
                                PADDING * (GRID_COLUMNS - 1)};
inline constexpr int WINDOW_HEIGHT{GRID_HEIGHT + PADDING * 2};
inline constexpr int WINDOW_WIDTH{GRID_WIDTH + PADDING * 2};

// colors
inline constexpr SDL_Color BACKGROUND_COLOR{170, 170, 170, 255};
inline constexpr SDL_Color BUTTON_COLOR{200, 200, 200, 255};
inline constexpr SDL_Color BUTTON_HOVER_COLOR{220, 220, 220, 255};

// asset path
inline const std::string BASE_PATH{SDL_GetBasePath()};
inline const std::string BOMB_IMAGE{BASE_PATH + "bomb.png"};
inline const std::string FLAG_IMAGE{BASE_PATH + "flag.png"};
inline const std::string FONT{BASE_PATH + "Roboto-Black.ttf"};

}  // namespace Config

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
    SDL_ClearError();
}
#endif
}  // namespace Utils
