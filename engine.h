#pragma once
#include "chessboard.h"

class Graphics;

class Engine
{
public:
    Engine(const std::string &title);

    void run();
    void stop();
    void input();

    SDL_Renderer *renderer;
    Graphics graphics;
    Chessboard chessboard;
    bool running;
};