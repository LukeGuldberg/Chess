#pragma once
#include "chessboard.h"

class Graphics;

class Engine
{
public:
    Engine(const std::string &title);

    void init();
    void run();
    void stop();
    bool input();

    SDL_Renderer *renderer;
    Graphics graphics;
    Chessboard chessboard;
    bool running;
    
private:
    Engine(const Engine &other); // copy constructor
    Engine &operator=(const Engine &rhs); // copy assignment
    Engine(Engine &&other); // move constructor
    Engine &operator=(Engine &&rhs); // move assignment
};