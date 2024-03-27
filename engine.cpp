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
            graphics.draw_board();
            graphics.draw_pieces(chessboard);
            graphics.highlight_tiles(chessboard, graphics);
            graphics.update();
            std::cout << "Position: " << chessboard.chessboard.at(chessboard.selected_piece_index).piece->pos << "\nType: " << chessboard.chessboard.at(chessboard.selected_piece_index).piece->type << "\n\n";
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
                graphics.tiles_to_highlight = {};
                int a, b;
                SDL_GetMouseState(&a, &b);
                int pos = chessboard.pixel_to_board(a, b, graphics);

                if (pos == -1)
                { // if mouse click is off of the board
                    chessboard.selected_piece_index = -1;
                    continue;
                }
                if (chessboard.chessboard.at(pos).piece && chessboard.chessboard.at(pos).piece->team_white)
                { // if piece exists and piece is on team white
                    chessboard.selected_piece_index = pos;
                    graphics.tiles_to_highlight = {pos};
                }
                else if (chessboard.chessboard.at(chessboard.selected_piece_index).piece && chessboard.is_valid_move(pos))
                { // if a white piece is selected, and the next spot clicked is a valid move
                    // chessboard.chessboard.at(pos).piece->pos = pos;
                    // chessboard.chessboard.at(chessboard.selected_piece_index).piece->pos = chessboard.selected_piece_index;
                    // chessboard.chessboard.at(pos).piece = chessboard.chessboard.at(chessboard.selected_piece_index).piece;
                    chessboard.chessboard.at(pos).piece.reset();
                    chessboard.chessboard.at(chessboard.selected_piece_index)
                        .piece.swap(chessboard.chessboard.at(pos).piece);
                    chessboard.chessboard.at(pos).piece->pos = pos;
                    chessboard.chessboard.at(chessboard.selected_piece_index).piece->pos = chessboard.selected_piece_index;

                    graphics.previous_move = {chessboard.selected_piece_index, pos}; // set previous move to be highlighted
                }

                if (chessboard.chessboard.at(chessboard.selected_piece_index).piece)
                {
                    graphics.tiles_to_highlight = chessboard.chessboard.at(chessboard.selected_piece_index).piece->get_possible_moves(chessboard);
                }
                // else
                //{
                //     graphics.tiles_to_highlight = {pos};
                // }
            }
            return true;
        }
    }
    return false;
}
