#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

class Chessboard;

class Graphics
{
public:
    Graphics(const std::string &title);
    ~Graphics();
    void clear();
    void update();
    // void draw_sprite(const Vec<int> &pixel, const Sprite &sprite);
    void initialize_graphics(const std::string title);
    void draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos);
    void draw_board();
    void draw_pieces(Chessboard &chessboard);
    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &path);

    // const int width, height;
    SDL_Renderer *renderer;

private:
    SDL_Window *window;

    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 900;
    const int BOARD_WIDTH = 728;
    const int GRID_SIZE = 8;
    const int V_PADDING = 86;
    const int H_PADDING = 436;
    const int TILE_SIZE = BOARD_WIDTH / GRID_SIZE;
};
