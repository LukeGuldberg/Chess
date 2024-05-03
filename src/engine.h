/* The engine class holds the game loop. This is what controls who moves what piece, where they move it to, and when they are able to move it. This is done by ither calling agent.find_best_move() to get the AI's best move, or allowing the user to make a move by handling an SDLMouseEvent (mouse click on the screen). This class also controls what is drawn to the screen using member functions within the Graphics class. The chessboard is redrawn every time a valid move or click is made. */
#pragma once
#include "agent.h"
#include "chessboard.h"

class Graphics;

class Engine {
   public:
    Engine(const std::string &title);

    void init();
    void run();
    void stop();
    bool input();

    int get_mouse_click(SDL_Event);
    void handle_mouse_click(int);
    void call_agent();
    void handle_agent_move(std::pair<int, int>);
    void set_possible_moves();
    void test_for_checks();

    Graphics graphics;
    Chessboard chessboard;
    Agent agent;
    bool running;

   private:
    Engine(const Engine &other) = delete;           // copy constructor
    Engine &operator=(const Engine &rhs) = delete;  // copy assignment
    Engine(Engine &&other) = delete;                // move constructor
    Engine &operator=(Engine &&rhs) = delete;       // move assignment
};