#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>

#include "engine.h"
#include "chessboard.h"

int main()
{
    Engine engine{"Chess"};
    engine.run();
}