/**
 * @file piece.h
 * @brief Finds possible moves given a Piece.
 *
 * The Piece class is used to store data like the pos and type of each piece. It is also used to find the possible moves for a piece. Each piece has a different function for this, and the pointers to these functions are stored in a vector to allow for constant time lookup.
 */
#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <optional>
#include <string>
#include <vector>

class Chessboard;
class Piece;

/// @brief Simplifies function pointer syntax for functions filling a vector possible_moves
using FuncPtr = void (*)(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);

enum Type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    KING,
    QUEEN
};

/// @brief Class structure for the pieces that fill a game state's board
class Piece {
   public:
    Piece(int pos, Type type, bool team_white);
    Piece(const Piece &other);
    Piece &operator=(const Piece &other);
    Piece(Piece &&other) noexcept;
    Piece &operator=(Piece &&other) noexcept;
    /// Returns possible moves for one piece
    std::vector<int> get_possible_moves(const Chessboard &chessboard);
    bool is_opposing_team(std::optional<Piece> other) const;

    int pos;
    Type type;
    bool team_white;

   private:
    /// Vector of functions that have corresponding possible_move functions, ordered to allow constant time lookups (see piece.h)
    std::vector<FuncPtr> find_move_functions;
};
void test_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_white_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_black_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_rook(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_bishop(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_knight(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_queen(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);
void test_king(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);