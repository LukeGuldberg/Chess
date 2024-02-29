#pragma once
#include "chessboard.h"
#include "camera.h"

class Graphics;

class Engine
{
public:
    Engine(const std::string &title);

    void run();
    void stop();

    SDL_Renderer *renderer;
    Graphics graphics;
    Camera camera;
    Chessboard chessboard;
    bool running;
};