#include "chessboard.h"
#include <string>
#include <iostream>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    // create all tiles
}
Chessboard::~Chessboard()
{
}

bool Chessboard::is_valid_move(int pos)
{
    std::vector<int> possible_moves = chessboard.at(selected_piece_index).piece->get_possible_moves(*this);
    for (int move : possible_moves)
    {
        if (pos == move)
        {
            return true;
        }
    }
    return false;
}

bool Chessboard::check_pixel_bounds(int x, int y, const Graphics &graphics) const
{
    if (x < graphics.left_bound || y < graphics.upper_bound || x > graphics.right_bound || y > graphics.bottom_bound)
    {
        return false;
    }
    return true;
}

int Chessboard::pixel_to_board(const int &x, const int &y, const Graphics &graphics) const
{
    if (check_pixel_bounds(x, y, graphics))
    {
        int index_y = ((y - graphics.upper_bound) / graphics.tile_size) * graphics.grid_size;
        int index_x = (x - graphics.left_bound) / graphics.tile_size;
        return index_x + index_y;
    }
    return -1;
}

std::pair<int, int> Chessboard::board_to_pixel(const int &i, const Graphics &graphics) const
{
    int x = ((i % graphics.grid_size) * graphics.tile_size) + graphics.left_bound;
    int y = ((i / graphics.grid_size) * graphics.tile_size) + graphics.upper_bound;

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

    // chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 8, ROOK, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 9, KNIGHT, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 10, BISHOP, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_queen.xcf", 11, QUEEN, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_king.xcf", 12, KING, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_bishop.xcf", 13, BISHOP, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_knight.xcf", 14, KNIGHT, false}});
    // chessboard.push_back(Tile{Piece{"../assets/b_rook.xcf", 15, ROOK, false}});
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

bool Tile::has_piece() const
{

    if (piece)
    {
        return true;
    }
    else
    {
        return false;
    }
    // return true ? piece: false;
}
