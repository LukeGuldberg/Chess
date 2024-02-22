#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <iostream>

#include "chessboard.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const int BOARD_WIDTH = 728;
const int BOARD_HEIGHT = 728;
const int GRID_SIZE = 8;
const int V_PADDING = 86;
const int H_PADDING = 436;
const int TILE_SIZE = BOARD_WIDTH / GRID_SIZE;

void drawGrid(SDL_Renderer *renderer);
void drawPieces(SDL_Renderer *renderer);

int main()
{
    Graphics graphics{"Chess", 1600, 900};
    Chessboard board{};
    // int result = SDL_Init(SDL_INIT_VIDEO);
    // if (result < 0)
    // {
    //     std::cout << SDL_GetError() << "\n";
    // }
    // SDL_Window *window =
    //     SDL_CreateWindow("Cool Game Title", SDL_WINDOWPOS_CENTERED,
    //                      SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    // if (!window)
    // {
    //     std::cout << SDL_GetError() << "\n";
    // }
    // SDL_Renderer *renderer = SDL_CreateRenderer(
    //     window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    bool running = true;
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
                    int tile_num = board.pixel_to_board(a, b);
                    std::cout << tile_num << "\n";
                }
            }
        }

        graphics.clear();
        drawGrid(graphics.renderer);
        drawPieces(graphics.renderer);
        graphics.update();
        // SDL_RenderPresent(renderer);
    }
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();
}

void drawGrid(SDL_Renderer *renderer)
{
    int TILE_SIZE = BOARD_WIDTH / GRID_SIZE;

    // Set color to white for grid lines
    SDL_SetRenderDrawColor(renderer, 165, 42, 42, 255);

    // Draw box
    SDL_RenderDrawLine(renderer, H_PADDING, V_PADDING, H_PADDING, SCREEN_HEIGHT - V_PADDING);
    SDL_RenderDrawLine(renderer, H_PADDING, V_PADDING, SCREEN_WIDTH - H_PADDING, V_PADDING);
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH - H_PADDING, V_PADDING, SCREEN_WIDTH - H_PADDING, SCREEN_HEIGHT - V_PADDING);
    SDL_RenderDrawLine(renderer, H_PADDING, SCREEN_HEIGHT - V_PADDING, SCREEN_WIDTH - H_PADDING, SCREEN_HEIGHT - V_PADDING);

    // Fill box
    for (int i = 1; i < GRID_SIZE; ++i)
    {
        SDL_RenderDrawLine(renderer, i * TILE_SIZE + H_PADDING, V_PADDING, i * TILE_SIZE + H_PADDING, SCREEN_HEIGHT - V_PADDING);
    }
    for (int i = 1; i < GRID_SIZE; ++i)
    {
        SDL_RenderDrawLine(renderer, H_PADDING, i * TILE_SIZE + V_PADDING, SCREEN_WIDTH - H_PADDING, i * TILE_SIZE + V_PADDING);
    }
}

void drawPieces(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Set color to white for filled rectangles
    for (int i = 0; i < 2; ++i)                       // Top 2 rows
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            SDL_Rect rect = {H_PADDING + j * TILE_SIZE + 25, V_PADDING + i * TILE_SIZE + 25, TILE_SIZE - 50, TILE_SIZE - 50};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    for (int i = GRID_SIZE - 2; i < GRID_SIZE; ++i) // Bottom 2 rows
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            SDL_Rect rect = {H_PADDING + j * TILE_SIZE + 25, V_PADDING + i * TILE_SIZE + 25, TILE_SIZE - 50, TILE_SIZE - 50};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}
