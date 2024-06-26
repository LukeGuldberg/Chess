/**
 * @file engine.cpp
 * @brief Contains main game loop and turn handling.
 *
 * The engine class holds the game loop. This is what controls who moves what piece, where they move it to, and when they are able to move it. This is done by ither calling agent.find_best_move() to get the AI's best move, or allowing the user to make a move by handling an SDLMouseEvent (mouse click on the screen). This class also controls what is drawn to the screen using member functions within the Graphics class. The chessboard is redrawn every time a valid move or click is made.
 */
#include "engine.h"

#include <iostream>

#include "graphics.h"

Engine::Engine(const std::string &title)
    : graphics{title}, chessboard{}, agent{chessboard} {}

void Engine::init() {
    graphics.draw_background();
    graphics.draw_board();
    graphics.draw_pieces(chessboard);
    graphics.update();
}

void Engine::run() {
    init();
    running = true;
    while (running) {
        if (input()) {
            graphics.clear();
            graphics.draw_background();
            graphics.draw_board();
            graphics.draw_pieces(chessboard);
            graphics.highlight_tiles(chessboard);
            graphics.update();
        }
    }
}
void Engine::stop() {
    running = false;
}

bool Engine::input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }

        int pos = get_mouse_click(event);
        if (chessboard.white_to_move && pos != -1) {  // pos clicked in bounds and white's turn
            handle_mouse_click(pos);
            test_for_checks();
            return true;
        } else if (!chessboard.white_to_move) {  // agent's/black's turn
            call_agent();
            test_for_checks();
            return true;
        }
    }
    return false;
}

void Engine::call_agent() {
    agent.reset_tree(chessboard);  // clears out the previous game state's tree of moves
    std::pair<int, int> best_move;
    int depth = 3;                            // how many moves ahead the agent will look
    best_move = agent.find_best_move(depth);  // depth is the param here
    handle_agent_move(best_move);
}

int Engine::get_mouse_click(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (SDL_BUTTON_LEFT == event.button.button) {
            graphics.selected_tile = -1;
            int a, b;
            SDL_GetMouseState(&a, &b);
            if (chessboard.in_bounds(graphics.pixel_to_board(a, b))) {
                return graphics.pixel_to_board(a, b);
            }
        }
    }
    return -1;
}

void Engine::handle_mouse_click(int pos) {
    if (chessboard.chessboard.at(pos).has_piece() && chessboard.chessboard.at(pos).piece->team_white) {
        // if piece exists and piece is on team white
        chessboard.selected_piece_index = pos;
        graphics.selected_tile = pos;
    } else if (chessboard.chessboard.at(chessboard.selected_piece_index).has_piece()) {
        // if a white piece is selected, and the next spot clicked is a valid move
        if (chessboard.move_piece(chessboard.selected_piece_index, pos)) {
            graphics.previous_move = {chessboard.selected_piece_index, pos};  // set previous move to be highlighted
        }
    } else {
        // invalid click
        std::cout << "Select one of your pieces\n";
    }
    if (graphics.show_possible_moves) {
        // if show possible moves is turned on
        set_possible_moves();
    }
}

void Engine::set_possible_moves() {
    if (chessboard.chessboard.at(chessboard.selected_piece_index).has_piece()) {
        // if piece exists
        graphics.possible_moves = chessboard.chessboard.at(chessboard.selected_piece_index).piece->get_possible_moves(chessboard);
    }
}

void Engine::test_for_checks() {
    if (chessboard.is_check()) {
        if (chessboard.white_to_move) {
            graphics.king_in_check = chessboard.w_king_index;
        } else {
            graphics.king_in_check = chessboard.b_king_index;
        }
        if (chessboard.is_checkmate()) {
            std::cout << "Checkmate!\n";
        } else {
            std::cout << "Check!\n";
        }

    } else {
        graphics.king_in_check = -1;
    }
}

void Engine::handle_agent_move(std::pair<int, int> best_move) {
    chessboard.move_piece(best_move.first, best_move.second);
}
