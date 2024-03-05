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
    bool is_opposing_team(const Piece &piece);

    std::string file_name;
    int pos;
    Type type;
    bool team_white;
};