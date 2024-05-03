/* The chessboard files are used to create, store, and make changes to data for a game state. Each game state is comprised of Tiles, and each Tile is able to have a Piece. It also has member functions that handle possible moves calculated in the piece files. The Chessboard class also differentiates between pseudo-legal moves and legal moves. This is done inside the is_valid_move() for testing one Piece's moves, and also in the is_checkmate() function which finds all legal moves for a given side. */
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

    std::vector<Tile> chessboard;  // game state

    std::vector<std::pair<int, int>> get_all_pseudo_moves();
    std::vector<std::pair<int, int>> get_all_legal_moves(std::vector<std::pair<int, int>> pseudo_legal);

    void update_piece_counts(const Tile &t);
    void recalculate_attackable_tiles();  // MUST BE CALLED AFTER EVERY MOVE
    std::set<int> attackable_by_white;    // all tiles attackable by white, duplicates thrown out
    std::set<int> attackable_by_black;    // all tiles attackable by black

    int selected_piece_index;  // store for highlighting and piece moves

    bool white_to_move;
    int w_king_index;  // store for a fast way to test for checks/mate
    int b_king_index;  // store for a fast way to test for checks/mate
    int w_num_pieces = 16;
    int b_num_pieces = 16;

    void swap_turn();
    bool move_piece(int start, int end);
    void move_piece_temp(int start, int end);
    int pixel_to_board(const int &x, const int &y, const Graphics &graphics) const;    // conversions used to go between board
    std::pair<int, int> board_to_pixel(const int &i, const Graphics &graphics) const;  // coordinates and screen pixel coordinates

    bool in_bounds(int pos);
    bool in_bounds(int row, int col);

   private:
    void fill_starting_tiles();
    void fill_test_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    bool check_pixel_bounds(int x, int y, const Graphics &graphics) const;
    bool test = false;

    std::vector<std::pair<int, int>> reshape_vector(std::vector<int> &possible_moves, int start);
};
