#include "graphics.h"
#include "chessboard.h"
#include "piece.h"

#include <SDL_image.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

Graphics::Graphics(const std::string &title)
{
    initialize_graphics(title);
    draw_board();
    // draw_pieces();
}

Graphics::~Graphics()
{
    // clean up: release SDL resources
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::clear()
{
    // clear the screen by painting it black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::update()
{
    SDL_RenderPresent(renderer);
}

void Graphics::initialize_graphics(const std::string title)
{
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0)
    {
        std::cout << SDL_GetError() << "\n";
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        std::cout << SDL_GetError() << "\n";
    }
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // initialize SDL, create a window and renderer
    // make sure to check all return values and throw exceptions when errors
    // occur

    if (!renderer)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // SDL2 image
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        throw std::runtime_error(IMG_GetError());
    }
}
void Graphics::draw_board()
{
    SDL_Texture *darkSquareTexture = loadTexture(renderer, "../assets/dark_square.xcf");
    SDL_Texture *lightSquareTexture = loadTexture(renderer, "../assets/light_square.xcf");
    if (!darkSquareTexture || !lightSquareTexture)
    {
        // Handle loading error
        std::cerr << "Failed to load texture(s) for board squares!" << std::endl;
        return;
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            SDL_Rect rectPos = {col * TILE_SIZE + H_PADDING, row * TILE_SIZE + V_PADDING, TILE_SIZE, TILE_SIZE};
            SDL_Texture *texture = (row + col) % 2 == 0 ? lightSquareTexture : darkSquareTexture;
            draw_sprite(texture, rectPos);
        }
    }
    SDL_DestroyTexture(darkSquareTexture);
    SDL_DestroyTexture(lightSquareTexture);
}

void Graphics::draw_pieces(Chessboard &chessboard)
{
    for (const Tile &t : chessboard.chessboard)
    {
        if (t.piece)
        {
            std::pair<int, int> pos = chessboard.board_to_pixel(t.piece->pos);
            SDL_Rect rectPos = {pos.first, pos.second, TILE_SIZE, TILE_SIZE};
            SDL_Texture *texture = loadTexture(renderer, t.piece->file_name);
            draw_sprite(texture, rectPos);
        }
    }
}

void Graphics::draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos)
{
    SDL_RenderCopy(renderer, spriteTexture, NULL, &rectPos);
}

SDL_Texture *Graphics::loadTexture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Unable to load image '" << path << "'! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
