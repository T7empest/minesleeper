#include "minesleeper/cell.h"

#include <SDL3/SDL.h>

#include <iostream>

#include "SDL3/SDL_events.h"
#include "globals.h"

MinesleeperCell::MinesleeperCell(int x, int y, int w, int h, int row, int col)
    : Button{x, y, w, h}, row_{row}, col_{col}
{
}

void MinesleeperCell::handle_event(const SDL_Event& e)
{
    Button::handle_event(e);
}

void MinesleeperCell::render(SDL_Surface* surface) { Button::render(surface); }
