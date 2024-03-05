#include "chessboard.h"
#include <string>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    // create all tiles
}

bool Chessboard::check_bounds(int x, int y) const
{
    if (x < 436 || y < 86 || x > 1164 || y > 814)
    {
        return false;
    }
    return true;
}

int Chessboard::pixel_to_board(const int &x, const int &y, const Graphics &graphics) const
{
    if (check_bounds(x, y))
    {
        int index_y = ((y - graphics.V_PADDING) / graphics.TILE_SIZE) * graphics.GRID_SIZE;
        int index_x = (x - graphics.H_PADDING) / graphics.TILE_SIZE;
        return index_x + index_y;
    }
    return -1;
}

std::pair<int, int> Chessboard::board_to_pixel(const int &i, const Graphics &graphics) const
{
    int x = ((i % graphics.GRID_SIZE) * graphics.TILE_SIZE) + graphics.H_PADDING;
    int y = ((i / graphics.GRID_SIZE) * graphics.TILE_SIZE) + graphics.V_PADDING;

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
    chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 0, ROOK, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 1, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 2, BISHOP, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_queen.xcf", 3, QUEEN, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_king.xcf", 4, KING, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 5, BISHOP, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 6, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 7, ROOK, false}});

    for (int i = 8; i < 16; ++i)
    {
        chessboard.push_back(Tile{Piece{"../assets/b_pawn.xcf", i, PAWN, false}});
    }
}

void Chessboard::place_starting_w_pieces()
{
    for (int i = 48; i < 56; ++i)
    {
        chessboard.push_back(Tile{Piece{"../assets/w_pawn.xcf", i, PAWN, true}});
    }
    chessboard.push_back(Tile{Piece{"../assets/w_rook.xcf", 56, ROOK, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_knight.xcf", 57, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_bishop.xcf", 58, BISHOP, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_queen.xcf", 59, QUEEN, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_king.xcf", 60, KING, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_bishop.xcf", 61, BISHOP, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_knight.xcf", 62, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{"../assets/w_rook.xcf", 63, ROOK, true}});

    
}

bool Chessboard::has_piece(int pos) const
{
    if (chessboard.at(pos).piece)
    {
        return true;
    }
    else
    {
        return false;
    }
    // return true ? chessboard.at(pos).piece: false;
}
