#include "engine.h"
#include "graphics.h"
#include <iostream>

Engine::Engine(const std::string &title)
    : graphics{title}
{
    renderer = graphics.renderer;
}

void Engine::run()
{
    running = true;
    while (running)
    {
        input();

        graphics.clear();
        graphics.draw_board();
        graphics.draw_pieces(chessboard);
        graphics.highlight_tiles(chessboard, graphics);
        graphics.update();
    }
}
void Engine::stop()
{
    running = false;
}

void Engine::input()
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
                {
                    continue;
                }
                if (chessboard.chessboard.at(pos).piece)
                {
                    graphics.tiles_to_highlight = chessboard.chessboard.at(pos).piece->get_possible_moves(chessboard);
                }
                else
                {
                    graphics.tiles_to_highlight = {pos};
                }
            }
        }
    }
}
