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
    Chessboard(Chessboard &&other);                 // move constructor
    Chessboard &operator=(Chessboard &&other);      // move assignment
    Chessboard(const Chessboard &other);            // copy constructor
    Chessboard &operator=(const Chessboard &other); // copy assignment
    bool is_valid_move(int start, int end);

    std::vector<Tile> chessboard;
    std::vector<Piece> taken_pieces; // nice to have -> show taken pieces next to board
    int selected_piece_index;

    void fill_starting_tiles();
    void fill_test_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    void move_piece(int start, int end);

    int pixel_to_board(const int &x, const int &y, const Graphics &graphics) const;
    std::pair<int, int> board_to_pixel(const int &i, const Graphics &graphics) const;

    bool in_bounds(int pos);
    bool in_bounds(int row, int col);

    int turn_counter;

    bool white_to_move = true;
    bool white_can_castle_kingside;
    bool white_can_castle_queenside;
    bool black_can_castle_kingside;
    bool black_can_castle_queenside;

private:
    bool check_pixel_bounds(int x, int y, const Graphics &graphics) const;
    bool test = false;
};
