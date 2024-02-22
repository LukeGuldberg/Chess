#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "sprite.h"
class Color
{
public:
    int red{255}, green{0}, blue{255}, alpha{255};
};

class Graphics
{
public:
    Graphics(const std::string &title, int window_width, int window_height);
    ~Graphics();
    void clear();
    void update();
    // void draw_sprite(const Vec<int> &pixel, const Sprite &sprite);
    void initialize_graphics(const std::string title);
    void draw_board();
    void draw_pieces();
    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &path);

    const int width, height;
    SDL_Renderer *renderer;

private:
    SDL_Window *window;
};
