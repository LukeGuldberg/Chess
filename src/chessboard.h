#pragma once
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "graphics.h"
#include "piece.h"

struct Tile {
    bool has_piece() const;
    std::optional<Piece> piece;
};

class Chessboard {
   public:
    Chessboard();
    ~Chessboard();
    Chessboard(Chessboard &&other);                  // move constructor
    Chessboard &operator=(Chessboard &&other);       // move assignment
    Chessboard(const Chessboard &other);             // copy constructor
    Chessboard &operator=(const Chessboard &other);  // copy assignment
    bool is_valid_move(int start, int end);
    bool is_check();
    bool is_checkmate();

    std::vector<Tile> chessboard;
    std::vector<Piece> taken_pieces;  // nice to have -> show taken pieces next to board

    std::vector<std::pair<int, int>> get_all_pseudo_moves();
    std::vector<std::pair<int, int>> get_all_legal_moves(std::vector<std::pair<int, int>> pseudo_legal);

    void recalculate_attackable_tiles();  // MUST BE CALLED AFTER EVERY MOVE
    std::set<int> attackable_by_white;    // all tiles that can be attacked by white
    std::set<int> attackable_by_black;

    std::vector<Piece> white_pinned_pieces;  // if piece is moved, would reveal check
    std::vector<Piece> black_pinned_pieces;

    std::vector<std::pair<int, int>> legal_moves;
    bool in_check = false;

    int selected_piece_index;  // store for highlighting

    int w_king_index;  // store for a fast way to test for checks/mate
    int b_king_index;  // store for a fast way to test for checks/mate

    void move_piece(int start, int end);
    void move_piece_temp(int start, int end);
    int pixel_to_board(const int &x, const int &y, const Graphics &graphics) const;
    std::pair<int, int> board_to_pixel(const int &i, const Graphics &graphics) const;

    bool in_bounds(int pos);
    bool in_bounds(int row, int col);

    bool white_to_move = true;

   private:
    void fill_starting_tiles();
    void fill_test_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    bool check_pixel_bounds(int x, int y, const Graphics &graphics) const;
    bool test = false;

    std::vector<std::pair<int, int>> reshape_vector(std::vector<int> &possible_moves, int start);
};
