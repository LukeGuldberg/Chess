/**
 * @file chessboard.h
 *
 * @brief Creates, stores, and makes changes to data for a game state.
 *
 * The chessboard files are used to create, store, and make changes to data for a game state. Each game state is comprised of Tiles, and each Tile is able to have a Piece. It also has member functions that handle possible moves calculated in the piece files. The Chessboard class also differentiates between pseudo-legal moves and legal moves. This is done inside the is_valid_move() for testing one Piece's moves, and also in the is_checkmate() function which finds all legal moves for a given side.
 */
#pragma once
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "graphics.h"
#include "piece.h"

/// @brief Comprises a Chessboard's game state, can hold a Piece
struct Tile {
    bool has_piece() const;
    std::optional<Piece> piece;
};

/// @brief Used to create, store, and make changes to a game state
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

    /// Game state
    std::vector<Tile> chessboard;
    /// Used for highlighting within graphics and also executing moves
    int selected_piece_index;
    /// True: white's turn | False: black's turn
    bool white_to_move;
    /// Store for a fast way to test for checks/mate
    int w_king_index;
    /// Store for a fast way to test for checks/mate
    int b_king_index;  
    int w_num_pieces = 16;
    int b_num_pieces = 16;

    bool move_piece(int start, int end);
    void move_piece_temp(int start, int end);
     
    bool in_bounds(int pos);
    bool in_bounds(int row, int col);

   private:
    void fill_starting_tiles();
    void fill_test_tiles();
    void place_starting_b_pieces();
    void place_starting_w_pieces();

    /// Pseudo-legal moves could be disallowed depending on how they affect the king.
    std::vector<std::pair<int, int>> get_all_pseudo_moves();
    /// Legal moves are 100% legal, takes king's position/state into consideration
    std::vector<std::pair<int, int>> get_all_legal_moves(std::vector<std::pair<int, int>> pseudo_legal);
    /// Recalculates w_num_pieces and b_num_pieces after every change to the game state
    void update_piece_counts(const Tile &t);
    /// Recalculates attackable_by_white and attackable_by_black after every change to the game state
    void recalculate_attackable_tiles();  // MUST BE CALLED AFTER EVERY MOVE
    /// All tiles attackable by white, duplicates discarded
    std::set<int> attackable_by_white;
    /// All tiles attackable by black, duplicates discarded
    std::set<int> attackable_by_black;    
    /// Flips value of white_to_move
    void swap_turn();

    bool test = false;

    std::vector<std::pair<int, int>> reshape_vector(std::vector<int> &possible_moves, int start);
};
