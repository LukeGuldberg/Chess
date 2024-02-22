#include "graphics.h"
// #include "randomness.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

Graphics::Graphics(const std::string &title, int window_width,
                   int window_height)
    : width{window_width}, height{window_height}
{
    initialize_graphics(title);
    draw_board();
    draw_pieces();
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
    // show the current canvas on the screen
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
                              SDL_WINDOWPOS_CENTERED, 1600, 900, 0);
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
