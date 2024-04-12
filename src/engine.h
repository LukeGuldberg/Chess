#pragma once
#include "chessboard.h"
#include "agent.h"

class Graphics;

class Engine
{
public:
    Engine(const std::string &title);

    void init();
    void run();
    void stop();
    bool input();

    void handle_mouse_click(Chessboard &, int);
    void handle_agent_move(Chessboard &, std::pair<int, int>);
    void set_possible_moves(Chessboard &);

    SDL_Renderer *renderer;
    Graphics graphics;
    Chessboard chessboard;
    Agent agent;
    bool running;

private:
    Engine(const Engine &other) = delete;          // copy constructor
    Engine &operator=(const Engine &rhs) = delete; // copy assignment
    Engine(Engine &&other) = delete;               // move constructor
    Engine &operator=(Engine &&rhs) = delete;      // move assignment
    };