#include "chessboard.h"
#include <string>
#include <iostream>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    turn_counter = 0;
    white_to_move = true;
    white_can_castle_kingside = true;
    white_can_castle_queenside = true;
    black_can_castle_kingside = true;
    black_can_castle_queenside = true;

    // create all tiles
}
Chessboard::~Chessboard() {}

Chessboard::Chessboard(const Chessboard &other) // copy constructor
    : chessboard{other.chessboard},
      taken_pieces{other.taken_pieces},
      selected_piece_index{other.selected_piece_index},
      white_to_move{other.white_to_move},
      white_can_castle_kingside{other.white_can_castle_kingside},
      white_can_castle_queenside{other.white_can_castle_queenside},
      black_can_castle_kingside{other.black_can_castle_kingside},
      black_can_castle_queenside{other.black_can_castle_queenside}
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
    chessboard.push_back(Tile{Piece{0, ROOK, false}});
    chessboard.push_back(Tile{Piece{1, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{2, BISHOP, false}});
    chessboard.push_back(Tile{Piece{3, QUEEN, false}});
    chessboard.push_back(Tile{Piece{4, KING, false}});
    chessboard.push_back(Tile{Piece{5, BISHOP, false}});
    chessboard.push_back(Tile{Piece{6, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{7, ROOK, false}});

    for (int i = 8; i < 16; ++i)
    {
        chessboard.push_back(Tile{Piece{i, PAWN, false}});
    }
}

void Chessboard::place_starting_w_pieces()
{
    for (int i = 48; i < 56; ++i)
    {
        chessboard.push_back(Tile{Piece{i, PAWN, true}});
    }

    chessboard.push_back(Tile{Piece{56, ROOK, true}});
    chessboard.push_back(Tile{Piece{57, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{58, BISHOP, true}});
    chessboard.push_back(Tile{Piece{59, QUEEN, true}});
    chessboard.push_back(Tile{Piece{60, KING, true}});
    chessboard.push_back(Tile{Piece{61, BISHOP, true}});
    chessboard.push_back(Tile{Piece{62, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{63, ROOK, true}});
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
    chessboard.clear();

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
        chessboard[i - 32].piece = Piece{i, PAWN, true};
    }

    // Move black pawns forward
    for (int i = 8; i < 16; ++i)
    {
        chessboard[i + 32].piece = Piece{i, PAWN, false};
    }

    // Move knights out
    chessboard.at(1).piece = Piece{1, KNIGHT, false};
    chessboard.at(6).piece = Piece{6, KNIGHT, false};
    chessboard.at(57).piece = Piece{57, KNIGHT, true};
    chessboard.at(62).piece = Piece{62, KNIGHT, true};

    // Move bishops out
    chessboard.at(2).piece = Piece{2, BISHOP, false};
    chessboard.at(5).piece = Piece{5, BISHOP, false};
    chessboard.at(58).piece = Piece{58, BISHOP, true};
    chessboard.at(61).piece = Piece{61, BISHOP, true};

    // Move rooks to corners
    chessboard.at(0).piece = Piece{0, ROOK, false};
    chessboard.at(7).piece = Piece{7, ROOK, false};
    chessboard.at(56).piece = Piece{56, ROOK, true};
    chessboard.at(63).piece = Piece{63, ROOK, true};

    // Place queens
    chessboard.at(3).piece = Piece{3, QUEEN, false};
    chessboard.at(59).piece = Piece{59, QUEEN, true};

    // Place kings
    chessboard.at(4).piece = Piece{4, KING, false};
    chessboard.at(60).piece = Piece{60, KING, true};
}