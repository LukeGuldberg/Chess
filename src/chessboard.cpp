#include "chessboard.h"
#include <string>
#include <iostream>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    turn_counter = 0;
    white_to_move = true;
    white_can_castle_kingside, white_can_castle_queenside,
        black_can_castle_kingside, black_can_castle_queenside = false;

    // create all tiles
}
Chessboard::~Chessboard() {}

Chessboard::Chessboard(const Chessboard &other) // copy constructor
    : chessboard(other.chessboard), taken_pieces(other.taken_pieces), selected_piece_index(other.selected_piece_index), white_to_move(other.white_to_move), white_can_castle_kingside(other.white_can_castle_kingside), white_can_castle_queenside(other.white_can_castle_queenside), black_can_castle_kingside(other.black_can_castle_kingside), black_can_castle_queenside(other.black_can_castle_queenside)
{
}
Chessboard &Chessboard::operator=(const Chessboard &other)
{
    chessboard = other.chessboard;
    taken_pieces = other.taken_pieces;
    selected_piece_index = other.selected_piece_index;
    white_to_move = other.white_to_move;
    white_can_castle_kingside = other.white_can_castle_kingside;
    white_can_castle_queenside = other.white_can_castle_queenside;
    black_can_castle_kingside = other.black_can_castle_kingside;
    black_can_castle_queenside = other.black_can_castle_queenside;
    return *this;
}

Chessboard::Chessboard(Chessboard &&other) // move constructor
    : chessboard(std::move(other.chessboard)),
      taken_pieces(std::move(other.taken_pieces)),
      selected_piece_index(other.selected_piece_index),
      white_to_move(other.white_to_move),
      white_can_castle_kingside(other.white_can_castle_kingside),
      white_can_castle_queenside(other.white_can_castle_queenside),
      black_can_castle_kingside(other.black_can_castle_kingside),
      black_can_castle_queenside(other.black_can_castle_queenside)
{
    other.selected_piece_index = -1;
    other.white_to_move = true;
    other.white_can_castle_kingside = true;
    other.white_can_castle_queenside = true;
    other.black_can_castle_kingside = true;
    other.black_can_castle_queenside = true;
}

Chessboard &Chessboard::operator=(Chessboard &&other) // move assignment operator
{
    if (this != &other)
    {
        chessboard = std::move(other.chessboard);
        taken_pieces = std::move(other.taken_pieces);
        selected_piece_index = other.selected_piece_index;
        white_to_move = other.white_to_move;
        white_can_castle_kingside = other.white_can_castle_kingside;
        white_can_castle_queenside = other.white_can_castle_queenside;
        black_can_castle_kingside = other.black_can_castle_kingside;
        black_can_castle_queenside = other.black_can_castle_queenside;

        other.selected_piece_index = -1;
        other.white_to_move = true;
        other.white_can_castle_kingside = true;
        other.white_can_castle_queenside = true;
        other.black_can_castle_kingside = true;
        other.black_can_castle_queenside = true;
    }
    return *this;
}

bool Chessboard::is_valid_move(int start, int end)
{
    std::vector<int> possible_moves = chessboard.at(start).piece->get_possible_moves(*this);
    for (int move : possible_moves)
    {
        if (end == move)
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

void Chessboard::move_piece(int start, int end)
{
    if (is_valid_move(start, end))
    {
        chessboard.at(end).piece.reset();
        chessboard.at(start).piece.swap(chessboard.at(end).piece);
        chessboard.at(end).piece->pos = end;
        chessboard.at(start).piece->pos = start;
        white_to_move = !white_to_move;
    }
}

void Chessboard::fill_test_tiles()
{
    // chessboard.clear();

    // Place black pieces
    place_starting_b_pieces();

    // Fill empty tiles for the middle of the board
    for (int i = 16; i < 48; ++i)
    {
        chessboard.push_back(Tile{});
    }

    // Place white pieces
    place_starting_w_pieces();

    // Additional moves to show a developed game
    // Move white pawns forward
    for (int i = 48; i < 56; ++i)
    {
        chessboard[i - 32].piece = Piece{"../assets/w_pawn.xcf", i, PAWN, true};
    }

    // Move black pawns forward
    for (int i = 8; i < 16; ++i)
    {
        chessboard[i + 32].piece = Piece{"../assets/b_pawn.xcf", i, PAWN, false};
    }

    // Move knights out
    chessboard[1].piece = Piece{"../assets/b_knight.xcf", 1, KNIGHT, false};
    chessboard[6].piece = Piece{"../assets/b_knight.xcf", 6, KNIGHT, false};
    chessboard[57].piece = Piece{"../assets/w_knight.xcf", 57, KNIGHT, true};
    chessboard[62].piece = Piece{"../assets/w_knight.xcf", 62, KNIGHT, true};

    // Move bishops out
    chessboard[2].piece = Piece{"../assets/b_bishop.xcf", 2, BISHOP, false};
    chessboard[5].piece = Piece{"../assets/b_bishop.xcf", 5, BISHOP, false};
    chessboard[58].piece = Piece{"../assets/w_bishop.xcf", 58, BISHOP, true};
    chessboard[61].piece = Piece{"../assets/w_bishop.xcf", 61, BISHOP, true};

    // Move rooks to corners
    chessboard[0].piece = Piece{"../assets/b_rook.xcf", 0, ROOK, false};
    chessboard[7].piece = Piece{"../assets/b_rook.xcf", 7, ROOK, false};
    chessboard[56].piece = Piece{"../assets/w_rook.xcf", 56, ROOK, true};
    chessboard[63].piece = Piece{"../assets/w_rook.xcf", 63, ROOK, true};

    // Place queens
    chessboard[3].piece = Piece{"../assets/b_queen.xcf", 3, QUEEN, false};
    chessboard[59].piece = Piece{"../assets/w_queen.xcf", 59, QUEEN, true};

    // Place kings
    chessboard[4].piece = Piece{"../assets/b_king.xcf", 4, KING, false};
    chessboard[60].piece = Piece{"../assets/w_king.xcf", 60, KING, true};
}