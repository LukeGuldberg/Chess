/**
 * @file graphics.h
 * @brief Handles all SDL2 functionalities require to visualize the game.
 *
 * The Graphics class is responsible for handling everything you see on the screen. It loads the sprites stored in /assets, draws them and any other changes of the board state to the screen using SDL2 functionalities.
 */
#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>
class Piece;
class Chessboard;

/// @brief Handles all SDL2 functionalities require to visualize the game.
class Graphics {
   public:
    Graphics(const std::string &title);
    ~Graphics();

    void clear();
    void update();

    void draw_background();
    void draw_board();
    void draw_pieces(Chessboard &chessboard);
    void highlight_tiles(const Chessboard &chessboard);

    bool check_pixel_bounds(int x, int y) const;
    /// Conversion used to go from screen pixel coordinates to board indices
    int pixel_to_board(const int &x, const int &y) const;
    /// Conversion used to go from board indices to screen pixel coordinates
    std::pair<int, int> board_to_pixel(const int &i) const;

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
    void load_sprites();
    void initialize_graphics(const std::string title);
    void destroy_textures();

    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Texture *loadTexture(SDL_Renderer *renderer, const std::string &path);
    SDL_Texture *find_texture(std::optional<Piece> piece);

    /// All types of piece textures stored allowing constant time lookup (find_texture())
    std::vector<SDL_Texture *> piece_textures;  
    SDL_Texture *dark_square_texture;
    SDL_Texture *light_square_texture;

    /// Called within
    void draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos);
    /// Called within highlight_tiles(const Chessboard &chessboard)
    void highlight_previous_move(const Chessboard &chessboard);
    /// Called within highlight_tiles(const Chessboard &chessboard)
    void highlight_selected_tile(const Chessboard &chessboard);
    /// Called within highlight_tiles(const Chessboard &chessboard)
    void highlight_possible_moves(const Chessboard &chessboard);
    /// Called within highlight_tiles(const Chessboard &chessboard)
    void highlight_king_in_check(const Chessboard &chessboard);

    Graphics(const Graphics &other) = delete;           // copy ctor
    Graphics &operator=(const Graphics &rhs) = delete;  // copy assignment operator
    Graphics(Graphics &&other) = delete;                // move ctor
    Graphics &operator=(Graphics &&rhs) = delete;       // move assignment
};
