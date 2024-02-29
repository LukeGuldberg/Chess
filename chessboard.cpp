#include "chessboard.h"
#include <string>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    // create all tiles
}

bool Chessboard::check_bounds(int x, int y)
{
    if (x < 436 || y < 86 || x > 1164 || y > 814)
    {
        return false;
    }
    return true;
}

int Chessboard::pixel_to_board(int x, int y)
{
    if (check_bounds(x, y))
    {
        int index_y = ((y - 86) / 91) * 8;
        int index_x = (x - 436) / 91;
        return index_x + index_y;
    }
    return -1;
}

std::pair<int, int> Chessboard::board_to_pixel(int i)
{
    int x = ((i % 8) * 91) + 436;
    int y = ((i / 8) * 91) + 86;

    std::pair<int, int> coordinate = {x, y};
    return coordinate;
}

void Chessboard::fill_starting_tiles()
{
    place_starting_b_pieces();
    // create tiles w/o pieces
    for (int i = 16; i < 48; ++i)
    {
        chessboard.push_back(Tile{});
    }
    place_starting_w_pieces();
}

void Chessboard::place_starting_b_pieces()
{
    chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 0, ROOK}});
    chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 1, KNIGHT}});
    chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 2, BISHOP}});
    chessboard.push_back(Tile{Piece{"../assets/b_queen.xcf", 3, QUEEN}});
    chessboard.push_back(Tile{Piece{"../assets/b_king.xcf", 4, KING}});
    chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 5, BISHOP}});
    chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 6, KNIGHT}});
    chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 7, ROOK}});

    for (int i = 8; i < 16; ++i)
    {
        chessboard.push_back(Tile{Piece{"../assets/b_pawn.xcf", i, PAWN}});
    }
}

void Chessboard::place_starting_w_pieces()
{
    chessboard.push_back(Tile{Piece{"../assets/w_rook.xcf", 56, ROOK}});
    chessboard.push_back(Tile{Piece{"../assets/w_knight.xcf", 57, KNIGHT}});
    chessboard.push_back(Tile{Piece{"../assets/w_bishop.xcf", 58, BISHOP}});
    chessboard.push_back(Tile{Piece{"../assets/w_queen.xcf", 59, QUEEN}});
    chessboard.push_back(Tile{Piece{"../assets/w_king.xcf", 60, KING}});
    chessboard.push_back(Tile{Piece{"../assets/w_bishop.xcf", 61, BISHOP}});
    chessboard.push_back(Tile{Piece{"../assets/w_knight.xcf", 62, KNIGHT}});
    chessboard.push_back(Tile{Piece{"../assets/w_rook.xcf", 63, ROOK}});

    for (int i = 48; i < 56; ++i)
    {
        chessboard.push_back(Tile{Piece{"../assets/w_pawn.xcf", i, PAWN}});
    }
}
