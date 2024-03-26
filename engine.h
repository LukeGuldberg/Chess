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
    Engine(const Engine &other) = delete; // copy constructor
    Engine &operator=(const Engine &rhs) = delete; // copy assignment
    Engine(Engine &&other) = delete;               // move constructor
    Engine &operator=(Engine &&rhs) = delete;      // move assignment
};