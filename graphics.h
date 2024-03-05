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

    const int SCREEN_WIDTH = 1600;
    const int SCREEN_HEIGHT = 900;
    const int BOARD_WIDTH = 728;
    const int GRID_SIZE = 8;
    const int V_PADDING = 86;
    const int H_PADDING = 436;
    const int TILE_SIZE = BOARD_WIDTH / GRID_SIZE;

private:
    SDL_Window *window;

    
};
