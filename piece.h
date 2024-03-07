#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

class Chessboard;

enum Type
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    KING,
    QUEEN
};

class Piece
{
public:
    Piece(std::string file_name, int pos, Type type, bool team_white);

    std::vector<int> get_possible_moves(const Chessboard &chessboard);
    bool is_opposing_team(const bool other);
    
    const std::string file_name;
    int pos;
    Type type;
    bool team_white;
private:
    void test_white_pawn(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_black_pawn(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_rook(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_bishop(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_knight(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_queen(std::vector<int> &possible_moves, const Chessboard &chessboard);
    void test_king(std::vector<int> &possible_moves, const Chessboard &chessboard);
};