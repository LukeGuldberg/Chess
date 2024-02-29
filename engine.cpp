#include "engine.h"
#include "graphics.h"
#include <iostream>

Engine::Engine(const std::string &title)
    : graphics{title}, camera{graphics, 91}
{
    renderer = graphics.renderer;
}

void Engine::run()
{
    running = true;
    while (running)
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
                    int a, b;
                    SDL_GetMouseState(&a, &b);

                    std::cout << a << " : " << b << "\n";
                    int tile_num = chessboard.pixel_to_board(a, b);
                    std::cout << tile_num << "\n";
                }
            }
        }

        graphics.clear();
        graphics.draw_board();
        graphics.draw_pieces(chessboard);
        graphics.update();
    }
}
void Engine::stop()
{
    running = false;
}
