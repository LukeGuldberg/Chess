/**
 * @file chessboard.cpp
 *
 * @brief Creates, stores, and makes changes to data for a game state.
 *
 * The chessboard files are used to create, store, and make changes to data for a game state. Each game state is comprised of Tiles, and each Tile is able to have a Piece. It also has member functions that handle possible moves calculated in the piece files. The Chessboard class also differentiates between pseudo-legal moves and legal moves. This is done inside the is_valid_move() for testing one Piece's moves, and also in the is_checkmate() function which finds all legal moves for a given side.
 */
#include "chessboard.h"

#include <iostream>
#include <string>

#include "piece.h"

Chessboard::Chessboard() {
    fill_starting_tiles();
    selected_piece_index = -1;
    white_to_move = true;
}
Chessboard::~Chessboard() {}

Chessboard::Chessboard(const Chessboard &other)  // copy constructor
    : chessboard{std::move(other.chessboard)},
      selected_piece_index{other.selected_piece_index},
      white_to_move{other.white_to_move},
      w_king_index{other.w_king_index},
      b_king_index{other.b_king_index},
      w_num_pieces{other.w_num_pieces},
      b_num_pieces{other.b_num_pieces} {}

Chessboard &Chessboard::operator=(const Chessboard &other) {
    chessboard = std::move(other.chessboard);
    selected_piece_index = other.selected_piece_index;
    white_to_move = other.white_to_move;
    w_king_index = other.w_king_index;
    b_king_index = other.b_king_index;
    w_num_pieces = other.w_num_pieces;
    b_num_pieces = other.b_num_pieces;
    return *this;
}

Chessboard::Chessboard(Chessboard &&other)  // move constructor
    : chessboard{std::move(other.chessboard)},
      selected_piece_index{other.selected_piece_index},
      white_to_move{other.white_to_move},
      w_king_index{other.w_king_index},
      b_king_index{b_king_index},
      w_num_pieces{other.w_num_pieces},
      b_num_pieces{other.b_num_pieces} {
    other.selected_piece_index = -1;
}

Chessboard &Chessboard::operator=(Chessboard &&other) {  // move assignment operator
    chessboard = std::move(other.chessboard);
    selected_piece_index = other.selected_piece_index;
    white_to_move = other.white_to_move;
    b_king_index = other.b_king_index;
    w_king_index = other.w_king_index;
    w_num_pieces = other.w_num_pieces;
    b_num_pieces = other.b_num_pieces;
    return *this;
}

bool Chessboard::is_valid_move(int start, int end) {
    if (in_bounds(start) && in_bounds(end)) {
        std::vector<int> possible_moves = chessboard.at(start).piece->get_possible_moves(*this);
        std::vector<std::pair<int, int>> pseudo_legal = reshape_vector(possible_moves, start);  // format to be a vector of pairs
        std::vector<std::pair<int, int>> legal = get_all_legal_moves(pseudo_legal);
        for (auto move : legal) {
            if (end == move.second && in_bounds(move.second)) {
                return true;
            }
        }
    }
    return false;
}

bool Chessboard::is_check() {
    if (!white_to_move) {
        for (int i : attackable_by_white) {
            if (i == b_king_index) {
                return true;
            }
        }
    } else {
        for (int i : attackable_by_black) {
            if (i == w_king_index) {
                return true;
            }
        }
    }
    return false;
}

bool Chessboard::is_checkmate() {
    std::vector<std::pair<int, int>> pseudo_legal = get_all_pseudo_moves();
    std::vector<std::pair<int, int>> legal_moves = get_all_legal_moves(pseudo_legal);
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
    // clear out data that is being recalculated
    attackable_by_black.clear();
    attackable_by_white.clear();
    w_num_pieces = 0;
    b_num_pieces = 0;
    for (Tile &t : chessboard) {
        if (t.has_piece()) {
            update_piece_counts(t);
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

void Chessboard::update_piece_counts(const Tile &t) {
    if (t.piece->team_white) {
        w_num_pieces++;
    } else {
        b_num_pieces++;
    }
}

void Chessboard::fill_starting_tiles() {
    place_starting_b_pieces();
    for (int i = 16; i < 48; ++i) {  // create tiles w/o pieces
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

void Chessboard::swap_turn() {
    white_to_move = !white_to_move;
}

bool Chessboard::move_piece(int start, int end) {
    if (is_valid_move(start, end)) {
        if (chessboard.at(start).piece->type == KING) {  // if King, update the position stored
            if (chessboard.at(start).piece->team_white) {
                w_king_index = end;
            } else {
                b_king_index = end;
            }
        }
        chessboard.at(end).piece.reset();                           // clear Tile the Piece is moving to
        chessboard.at(start).piece.swap(chessboard.at(end).piece);  // swap the two Tiles
        chessboard.at(end).piece->pos = end;                        // reset the indices after swap
        chessboard.at(start).piece->pos = start;                    // to preserve the order of the board
        recalculate_attackable_tiles();
        swap_turn();
        return true;
    }
    return false;
}

void Chessboard::move_piece_temp(int start, int end) {  // excludes a test of is_valid_move(), used when looking for checkmates to save on runtime
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