#include "engine.h"
#include "graphics.h"
#include <iostream>

Engine::Engine(const std::string &title)
    : graphics{title}
{
    renderer = graphics.renderer;
}

void Engine::init()
{
    graphics.draw_background();
    graphics.draw_board();
    graphics.draw_pieces(chessboard);
    graphics.update();
}

void Engine::run()
{
    init();
    running = true;
    while (running)
    {
        if (input())
        {
            graphics.clear();
            graphics.draw_background();
            graphics.draw_board();
            graphics.draw_pieces(chessboard);
            graphics.highlight_tiles(chessboard, graphics);
            graphics.update();
        }
    }
}
void Engine::stop()
{
    running = false;
}

bool Engine::input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
            break;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (SDL_BUTTON_LEFT == event.button.button)
            {
                graphics.selected_tile = -1;
                int a, b;
                SDL_GetMouseState(&a, &b);
                int pos = chessboard.pixel_to_board(a, b, graphics);

                if (pos == -1)
                {   // if mouse click is off of the board
                    chessboard.selected_piece_index = -1;
                    continue;
                }
                
                if (chessboard.chessboard.at(pos).piece && chessboard.chessboard.at(pos).piece->team_white)
                {   // if piece exists and piece is on team white
                    chessboard.selected_piece_index = pos;
                    graphics.selected_tile = pos;
                }
                else if (chessboard.chessboard.at(chessboard.selected_piece_index).piece && chessboard.is_valid_move(pos))
                {   // if a white piece is selected, and the next spot clicked is a valid move
                    
                    if (chessboard.chessboard.at(pos).piece) {
                        chessboard.taken_pieces.push_back(std::move(chessboard.chessboard.at(pos).piece.value()));
                    }
                    chessboard.chessboard.at(pos).piece.reset();
                    chessboard.chessboard.at(chessboard.selected_piece_index).piece.swap(chessboard.chessboard.at(pos).piece);
                    chessboard.chessboard.at(pos).piece->pos = pos;
                    chessboard.chessboard.at(chessboard.selected_piece_index).piece->pos = chessboard.selected_piece_index;

                    graphics.previous_move = {chessboard.selected_piece_index, pos}; // set previous move to be highlighted
                }
                if (chessboard.chessboard.at(chessboard.selected_piece_index).piece && graphics.show_possible_moves)
                {   // if show possible moves is turned on
                    graphics.possible_moves = chessboard.chessboard.at(chessboard.selected_piece_index).piece->get_possible_moves(chessboard);
                }
            }
            return true;
        }
    }
    return false;
}
