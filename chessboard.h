#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "piece.h"
#include "graphics.h"

struct Tile
{
    std::optional<Piece> piece; // std::optional
};

class Chessboard
{
public:
    Chessboard();

    std::vector<Tile> chessboard;
    void fill_starting_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    int pixel_to_board(int x, int y);
    std::pair<int, int> board_to_pixel(int i);

    bool check_bounds(int x, int y);
};
