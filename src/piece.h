#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include <optional>
#include <string>
#include <vector>

class Chessboard;
class Piece;

using FuncPtr = void (*)(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard);

enum Type {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    KING,
    QUEEN
};

class Piece {
   public:
    Piece(int pos, Type type, bool team_white);
    Piece(const Piece &other);
    Piece &operator=(const Piece &other);
    Piece(Piece &&other) noexcept;
    Piece &operator=(Piece &&other) noexcept;

    std::vector<int> get_possible_moves(const Chessboard &chessboard);
    bool is_opposing_team(std::optional<Piece> other) const;

    int pos;
    Type type;
    bool team_white;

   private:
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