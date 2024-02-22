#pragma once
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

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
    Piece(std::string file_name, int pos, Type type);
    std::string file_name;
    int pos;
    Type type;
};