/**
 * @file engine.h
 * @brief Contains main game loop and turn handling.
 *
 * The engine class holds the game loop. This is what controls who moves what piece, where they move it to, and when they are able to move it. This is done by ither calling agent.find_best_move() to get the AI's best move, or allowing the user to make a move by handling an SDLMouseEvent (mouse click on the screen). This class also controls what is drawn to the screen using member functions within the Graphics class. The chessboard is redrawn every time a valid move or click is made.
 */
#pragma once
#include "agent.h"
#include "chessboard.h"

class Graphics;

/// Contains main game loop and turn handling.
class Engine {
   public:
    Engine(const std::string &title);
    /// Game loop
    void run();

   private:
    Graphics graphics;
    /// Game state
    Chessboard chessboard;
    /// AI component to play against
    Agent agent;
    bool running;

    /// Draw the screen for the first time
    void init();
    /// End game loop
    void stop();
    /// Returns true if there is a change to the game state, triggers screen to be redrawn
    bool input();
    /// Returns the Tile number selected from the SDLMouseEvent
    int get_mouse_click(SDL_Event);
    /// Handles user input depending on what Tile was selected from get_mouse_click(SDL_Event)
    void handle_mouse_click(int);
    /// Black's turn, call Agent find_best_move(depth) to decide on a best move
    void call_agent();
    /// Apply Agent's move
    void handle_agent_move(std::pair<int, int>);
    /// Show possible moves for each Piece when selected if enabled
    void set_possible_moves();
    /// Test for checks/mates after every change to the game state
    void test_for_checks();

    Engine(const Engine &other) = delete;           // copy constructor
    Engine &operator=(const Engine &rhs) = delete;  // copy assignment
    Engine(Engine &&other) = delete;                // move constructor
    Engine &operator=(Engine &&rhs) = delete;       // move assignment
};