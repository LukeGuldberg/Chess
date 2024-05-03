/* The Graphics class is responsible for handling everything you see on the screen. It loads the sprites stored in /assets, draws them and any other changes of the board state to the screen using SDL2 functionalities. */
#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>
class Piece;
class Chessboard;

class Graphics {
   public:
    Graphics(const std::string &title);

    ~Graphics();
    void destroy_textures();

    void clear();
    void update();
    void load_sprites();
    void initialize_graphics(const std::string title);

    SDL_Texture *find_texture(std::optional<Piece> piece);

    void draw_background();
    void draw_board();
    void draw_pieces(Chessboard &chessboard);
    void draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos);
    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &path);

    void highlight_tiles(const Chessboard &chessboard);
    void highlight_previous_move(const Chessboard &chessboard);
    void highlight_selected_tile(const Chessboard &chessboard);
    void highlight_possible_moves(const Chessboard &chessboard);
    void highlight_king_in_check(const Chessboard &chessboard);

    SDL_Renderer *renderer;
    int selected_tile = -1;
    int king_in_check = -1;
    std::vector<int> previous_move;
    std::vector<int> possible_moves;

    bool show_possible_moves = false;
    const int grid_size = 8;  // 8x8
    // variables below are in pixels
    const int screen_width = 1600;
    const int screen_height = 900;
    const int board_width = 728;
    const int upper_bound = 86;
    const int left_bound = 436;
    const int bottom_bound = 814;
    const int right_bound = 1164;
    const int tile_size = board_width / grid_size;

   private:
    SDL_Window *window;

    std::vector<SDL_Texture *> piece_textures;  // all types of piece textures stored allowing constant time lookup (find_texture())
    SDL_Texture *dark_square_texture;
    SDL_Texture *light_square_texture;

    Graphics(const Graphics &other) = delete;           // copy ctor
    Graphics &operator=(const Graphics &rhs) = delete;  // copy assignment operator
    Graphics(Graphics &&other) = delete;                // move ctor
    Graphics &operator=(Graphics &&rhs) = delete;       // move assignment
};
