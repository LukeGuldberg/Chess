#include "chessboard.h"

#include <iostream>
#include <string>

#include "piece.h"

Chessboard::Chessboard() {
    fill_starting_tiles();
    selected_piece_index = -1;
    white_to_move = true;

    // create all tiles
}
Chessboard::~Chessboard() {}

Chessboard::Chessboard(const Chessboard &other)  // copy constructor
    : chessboard{other.chessboard},
      taken_pieces{other.taken_pieces},
      selected_piece_index{other.selected_piece_index},
      white_to_move{other.white_to_move},
      w_king_index{other.w_king_index},
      b_king_index{b_king_index} {}
Chessboard &Chessboard::operator=(const Chessboard &other) {
    chessboard = other.chessboard;
    taken_pieces = other.taken_pieces;
    selected_piece_index = other.selected_piece_index;
    white_to_move = other.white_to_move;
    b_king_index = other.b_king_index;
    w_king_index = other.w_king_index;

    return *this;
}

Chessboard::Chessboard(Chessboard &&other)  // move constructor
    : chessboard{std::move(other.chessboard)},
      taken_pieces{std::move(other.taken_pieces)},
      selected_piece_index{other.selected_piece_index},
      white_to_move{other.white_to_move},
      w_king_index{other.w_king_index},
      b_king_index{b_king_index} {
    other.selected_piece_index = -1;
    other.white_to_move = true;
}

Chessboard &Chessboard::operator=(Chessboard &&other)  // move assignment operator
{
    chessboard = std::move(other.chessboard);
    taken_pieces = std::move(other.taken_pieces);
    selected_piece_index = other.selected_piece_index;
    white_to_move = other.white_to_move;
    b_king_index = other.b_king_index;
    w_king_index = other.w_king_index;

    other.selected_piece_index = -1;
    other.white_to_move = true;

    return *this;
}

bool Chessboard::is_valid_move(int start, int end) {
    std::vector<int> possible_moves = chessboard.at(start).piece->get_possible_moves(*this);
    std::vector<std::pair<int, int>> pseudo_legal = reshape_vector(possible_moves, start);
    std::vector<std::pair<int, int>> legal = get_all_legal_moves(pseudo_legal);
    for (auto move : legal) {
        if (end == move.second && in_bounds(move.second)) {
            return true;
        }
    }

    return false;
}

bool Chessboard::is_check() {
    if (!white_to_move) {
        for (int i : attackable_by_white) {
            if (i == b_king_index) {
                in_check = true;
                return true;
            }
        }
    } else {
        for (int i : attackable_by_black) {
            if (i == w_king_index) {
                in_check = true;
                return true;
            }
        }
    }
    in_check = false;
    return false;
}

bool Chessboard::is_checkmate() {
    std::vector<std::pair<int, int>> pseudo_legal = get_all_pseudo_moves();
    legal_moves = get_all_legal_moves(pseudo_legal);
    return legal_moves.empty();  // If no move could be found to prevent mate, then it is a mate
}

std::vector<std::pair<int, int>> Chessboard::get_all_pseudo_moves() {
    // Get all pseudo-legal moves for the current player
    std::vector<std::pair<int, int>> pseudo_legal;
    for (Tile &t : chessboard) {
        if (t.has_piece() && t.piece->team_white == white_to_move) {
            std::vector<int> moves = t.piece->get_possible_moves(*this);
            for (int move : moves) {
                pseudo_legal.push_back({t.piece->pos, move});
            }
        }
    }
    return pseudo_legal;
}

std::vector<std::pair<int, int>> Chessboard::get_all_legal_moves(std::vector<std::pair<int, int>> pseudo_legal) {
    std::vector<std::pair<int, int>> legal;
    // For each move, check if opponent's king is still in checkmate after the move
    for (auto move : pseudo_legal) {
        Chessboard temp_board(*this);
        temp_board.move_piece_temp(move.first, move.second);  // Apply the move to a temporary board
        if (!temp_board.is_check()) {                         // Check if the king is still in check
            legal.push_back(move);                            // Move prevents checkmate, so save as legal move
        }
    }
    return legal;
}

void Chessboard::recalculate_attackable_tiles() {
    attackable_by_black.clear();
    attackable_by_white.clear();
    for (Tile &t : chessboard) {
        if (t.has_piece()) {
            std::vector<int> possible_moves = t.piece->get_possible_moves(*this);
            if (t.piece->team_white) {
                for (int i : possible_moves) {
                    attackable_by_white.insert(i);
                }
            } else {
                for (int i : possible_moves) {
                    attackable_by_black.insert(i);
                }
            }
        }
    }
}

bool Chessboard::check_pixel_bounds(int x, int y, const Graphics &graphics) const {
    if (x < graphics.left_bound || y < graphics.upper_bound || x > graphics.right_bound || y > graphics.bottom_bound) {
        return false;
    }
    return true;
}

int Chessboard::pixel_to_board(const int &x, const int &y, const Graphics &graphics) const {
    if (check_pixel_bounds(x, y, graphics)) {
        int index_y = ((y - graphics.upper_bound) / graphics.tile_size) * graphics.grid_size;
        int index_x = (x - graphics.left_bound) / graphics.tile_size;
        return index_x + index_y;
    }
    return -1;
}

std::pair<int, int> Chessboard::board_to_pixel(const int &i, const Graphics &graphics) const {
    int x = ((i % graphics.grid_size) * graphics.tile_size) + graphics.left_bound;
    int y = ((i / graphics.grid_size) * graphics.tile_size) + graphics.upper_bound;

    std::pair<int, int> coordinate = {x, y};
    return coordinate;
}

void Chessboard::fill_starting_tiles() {
    place_starting_b_pieces();
    // create tiles w/o pieces
    for (int i = 16; i < 48; ++i) {
        chessboard.push_back(Tile{});
    }
    place_starting_w_pieces();
}

void Chessboard::place_starting_b_pieces() {
    chessboard.push_back(Tile{Piece{0, ROOK, false}});
    chessboard.push_back(Tile{Piece{1, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{2, BISHOP, false}});
    chessboard.push_back(Tile{Piece{3, QUEEN, false}});
    chessboard.push_back(Tile{Piece{4, KING, false}});
    b_king_index = 4;
    chessboard.push_back(Tile{Piece{5, BISHOP, false}});
    chessboard.push_back(Tile{Piece{6, KNIGHT, false}});
    chessboard.push_back(Tile{Piece{7, ROOK, false}});

    for (int i = 8; i < 16; ++i) {
        chessboard.push_back(Tile{Piece{i, PAWN, false}});
    }
}

void Chessboard::place_starting_w_pieces() {
    for (int i = 48; i < 56; ++i) {
        chessboard.push_back(Tile{Piece{i, PAWN, true}});
    }

    chessboard.push_back(Tile{Piece{56, ROOK, true}});
    chessboard.push_back(Tile{Piece{57, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{58, BISHOP, true}});
    chessboard.push_back(Tile{Piece{59, QUEEN, true}});
    chessboard.push_back(Tile{Piece{60, KING, true}});
    w_king_index = 60;
    chessboard.push_back(Tile{Piece{61, BISHOP, true}});
    chessboard.push_back(Tile{Piece{62, KNIGHT, true}});
    chessboard.push_back(Tile{Piece{63, ROOK, true}});
}

bool Tile::has_piece() const {
    if (piece) {
        return true;
    } else {
        return false;
    }
}

void Chessboard::move_piece(int start, int end) {
    if (is_valid_move(start, end)) {
        if (chessboard.at(start).piece->type == KING) {
            if (chessboard.at(start).piece->team_white) {
                w_king_index = end;
            } else {
                b_king_index = end;
            }
        }
        chessboard.at(end).piece.reset();
        chessboard.at(start).piece.swap(chessboard.at(end).piece);
        chessboard.at(end).piece->pos = end;
        chessboard.at(start).piece->pos = start;
        recalculate_attackable_tiles();
    }
}

void Chessboard::move_piece_temp(int start, int end) {
    if (chessboard.at(start).piece->type == KING) {
        if (chessboard.at(start).piece->team_white) {
            w_king_index = end;
        } else {
            b_king_index = end;
        }
    }

    chessboard.at(end).piece.reset();
    chessboard.at(start).piece.swap(chessboard.at(end).piece);
    chessboard.at(end).piece->pos = end;
    chessboard.at(start).piece->pos = start;
    recalculate_attackable_tiles();
}

bool Chessboard::in_bounds(int pos) {
    if (pos < 64 && pos >= 0) {
        return true;
    }
    return false;
}
bool Chessboard::in_bounds(int row, int col) {
    int pos = col + row * 8;
    if (pos < 64 && pos >= 0) {
        return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Chessboard::reshape_vector(std::vector<int> &possible_moves, int start) {
    std::vector<std::pair<int, int>> new_moves;
    for (int i : possible_moves) {
        new_moves.push_back({start, i});
    }
    return new_moves;
}

void Chessboard::fill_test_tiles() {
    chessboard.clear();

    // Place black pieces
    place_starting_b_pieces();

    // Fill empty tiles for the middle of the board
    for (int i = 16; i < 48; ++i) {
        chessboard.push_back(Tile{});
    }

    // Place white pieces
    place_starting_w_pieces();

    // Additional moves to show a developed game
    // Move white pawns forward
    for (int i = 48; i < 56; ++i) {
        chessboard[i - 32].piece = Piece{i, PAWN, true};
    }

    // Move black pawns forward
    for (int i = 8; i < 16; ++i) {
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