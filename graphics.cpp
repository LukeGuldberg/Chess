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
    darkSquareTexture = loadTexture(renderer, "../assets/dark_square.xcf");
    lightSquareTexture = loadTexture(renderer, "../assets/light_square.xcf");
}

Graphics::Graphics(Graphics &&other)
    : renderer{other.renderer}, window{other.window}, darkSquareTexture{other.darkSquareTexture}, lightSquareTexture{other.lightSquareTexture}, tiles_to_highlight{other.tiles_to_highlight}
{
    other.renderer = nullptr;
    other.window = nullptr;
    other.darkSquareTexture = nullptr;
    other.lightSquareTexture = nullptr;
}

Graphics &Graphics::operator=(Graphics &&rhs){
    std::swap(renderer, rhs.renderer);
    std::swap(window, rhs.window);
    std::swap(darkSquareTexture, rhs.darkSquareTexture);
    std::swap(lightSquareTexture, rhs.lightSquareTexture);
    return *this;
}

Graphics::~Graphics()
{
    // clean up: release SDL resources
    SDL_DestroyTexture(lightSquareTexture);
    SDL_DestroyTexture(darkSquareTexture);
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
                              SDL_WINDOWPOS_CENTERED, screen_width, screen_height, 0);
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
            SDL_Rect rectPos = {col * tile_size + left_bound, row * tile_size + upper_bound, tile_size, tile_size};
            if ((row + col) % 2 == 0)
            {
                draw_sprite(lightSquareTexture, rectPos);
            }
            else
            {
                draw_sprite(darkSquareTexture, rectPos);
            }
        }
    }
}

void Graphics::draw_pieces(Chessboard &chessboard)
{
    for (const Tile &t : chessboard.chessboard)
    {
        if (t.piece)
        {
            std::pair<int, int> pos = chessboard.board_to_pixel(t.piece->pos, *this);
            SDL_Rect rectPos = {pos.first, pos.second, tile_size, tile_size};
            SDL_Texture *texture = loadTexture(renderer, t.piece->file_name);
            draw_sprite(texture, rectPos);

            SDL_DestroyTexture(texture);
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

void Graphics::highlight_tiles(const Chessboard &chessboard, const Graphics &graphics)
{
    //change to highlight previous move and currect selected tile, do not highlight all possible moves but keep that feature for testing
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
    for (const int &pos : tiles_to_highlight)
    {
        if (pos == -1)
        {
            break;
        }
        auto position = chessboard.board_to_pixel(pos, graphics);
        SDL_Rect rectPos = {position.first, position.second, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &rectPos);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
