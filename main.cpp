#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>

#include "engine.h"
#include "chessboard.h"



void drawGrid(SDL_Renderer *renderer);
void drawPieces(SDL_Renderer *renderer);

int main()
{
    Engine engine{"Chess"};
    engine.run();
}