#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <vector>

class Chessboard;

class Graphics
{
public:
    Graphics(const std::string &title);
    Graphics(Graphics &&other);
    Graphics &operator=(Graphics &&rhs);
    ~Graphics();

    void clear();
    void update();
    void initialize_graphics(const std::string title);
    void draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos);
    void draw_board();
    void draw_pieces(Chessboard &chessboard);
    void highlight_tiles(const Chessboard &chessboard, const Graphics &graphics);
    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &path);

    SDL_Renderer *renderer;
    std::vector<int> tiles_to_highlight;

    const int screen_width = 1600;
    const int screen_height = 900;
    const int board_width = 728;
    const int grid_size = 8;
    const int upper_bound = 86; // upper bound
    const int left_bound = 436; // left bound
    const int bottom_bound = 814;
    const int right_bound = 1164;
    const int tile_size = board_width / grid_size;

private:
    SDL_Window *window;
    SDL_Texture *darkSquareTexture;
    SDL_Texture *lightSquareTexture;

    Graphics(const Graphics &other); // copy constructor
    Graphics &operator=(const Graphics &rhs); // copy assignment operator
};
