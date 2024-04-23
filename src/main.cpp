#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "chessboard.h"
#include "engine.h"

int main() {
    Engine engine{"Chess"};
    engine.run();
}