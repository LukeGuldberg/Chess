#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "piece.h"
#include "graphics.h"

struct Tile
{
    bool has_piece() const;
    std::optional<Piece> piece; // std::optional
};

class Chessboard
{
public:
    Chessboard();
    ~Chessboard();
    // Chessboard(Chessboard &&other);
    // Chessboard &operator=(Chessboard &&rhs);

    bool is_valid_move(int pos);

    std::vector<Tile> chessboard;
    int selected_piece_index;
    void fill_starting_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    int  pixel_to_board(const int &x, const int &y, const Graphics &graphics) const;
    std::pair<int, int> board_to_pixel(const int &i, const Graphics &graphics) const;

    // bool has_piece(int pos) const;
private:
    bool check_pixel_bounds(int x, int y, const Graphics &graphics) const;

    // Chessboard(const Chessboard &other);  // copy constructor
    // Chessboard &operator=(const Chessboard &rhs); //copy assignment
};
