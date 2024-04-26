#include "piece.h"

#include <iostream>

#include "chessboard.h"

Piece::Piece(int pos, Type type, bool team_white)
    : pos{pos},
      type{type},
      team_white{team_white} {
    find_move_functions = {&test_pawn, &test_knight,
                           &test_bishop, &test_rook,
                           &test_king, &test_queen};
}

Piece::Piece(const Piece &other)
    : pos{other.pos},
      type{other.type},
      team_white{other.team_white},
      find_move_functions{other.find_move_functions} {}

Piece &Piece::operator=(const Piece &other) {
    pos = other.pos;
    type = other.type;
    team_white = other.team_white;
    find_move_functions = other.find_move_functions;
    return *this;
}

Piece::Piece(Piece &&other) noexcept
    : pos(other.pos),
      type(other.type),
      team_white(other.team_white),
      find_move_functions{other.find_move_functions} {}

Piece &Piece::operator=(Piece &&other) noexcept {
    type = other.type;
    std::swap(pos, other.pos);
    team_white = other.team_white;
    find_move_functions = other.find_move_functions;
    return *this;
}

std::vector<int> Piece::get_possible_moves(const Chessboard &chessboard) {
    std::vector<int> possible_moves;
    auto func = find_move_functions.at(type);
    func(*this, possible_moves, chessboard);
    return possible_moves;
}

bool Piece::is_opposing_team(std::optional<Piece> other) const {
    if (!other) {  // if other doesn't exist
        return true;
    }
    return !team_white == other->team_white;  // true if not same team
}

void test_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    if (piece.team_white) {
        test_white_pawn(piece, possible_moves, chessboard);
    } else {
        test_black_pawn(piece, possible_moves, chessboard);
    }
}

void test_white_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int forward_one = piece.pos - 8;
    int forward_two = piece.pos - 16;

    if (!chessboard.chessboard.at(forward_one).has_piece()) {  // check one square forward
        possible_moves.push_back(forward_one);

        // check two squares forward from starting position
        if ((piece.pos < 56 && piece.pos > 47) && !chessboard.chessboard.at(forward_two).has_piece()) {
            possible_moves.push_back(forward_two);
        }
    }

    // check diagonal left attacking move
    int left_attack = piece.pos - 9;
    if (piece.pos % 8 != 0 && chessboard.chessboard.at(left_attack).piece && piece.is_opposing_team(chessboard.chessboard.at(left_attack).piece)) {
        possible_moves.push_back(left_attack);
    }

    // check diagonal right attacking move
    int right_attack = piece.pos - 7;
    if (piece.pos % 8 != 7 && chessboard.chessboard.at(right_attack).piece && piece.is_opposing_team(chessboard.chessboard.at(right_attack).piece)) {
        possible_moves.push_back(right_attack);
    }
}

void test_black_pawn(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int forward_one = piece.pos + 8;
    int forward_two = piece.pos + 16;

    // check one square forward
    if (!chessboard.chessboard.at(forward_one).has_piece()) {
        possible_moves.push_back(forward_one);

        // check two squares forward from starting position
        if ((piece.pos < 16 && piece.pos > 7) && !chessboard.chessboard.at(forward_two).has_piece()) {
            possible_moves.push_back(forward_two);
        }
    }

    // check diagonal left attacking move
    int left_attack = piece.pos + 7;
    if (piece.pos % 8 != 0 && chessboard.chessboard.at(left_attack).piece && piece.is_opposing_team(chessboard.chessboard.at(left_attack).piece)) {
        possible_moves.push_back(left_attack);
    }

    // check diagonal right attacking move
    int right_attack = piece.pos + 9;
    if (piece.pos % 8 != 7 && chessboard.chessboard.at(right_attack).piece && piece.is_opposing_team(chessboard.chessboard.at(right_attack).piece)) {
        possible_moves.push_back(right_attack);
    }
}

void test_rook(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int row = piece.pos % 8;
    int col = piece.pos / 8;

    // check upward
    for (int c = col + 1; c < 8; ++c) {
        int new_pos = c * 8 + row;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check downward
    for (int c = col - 1; c >= 0; --c) {
        int new_pos = c * 8 + row;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check to the right
    for (int r = row + 1; r < 8; ++r) {
        int new_pos = col * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check to the left
    for (int r = row - 1; r >= 0; --r) {
        int new_pos = col * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }
}

void test_bishop(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int row = piece.pos % 8;
    int col = piece.pos / 8;

    // check up right
    for (int c = col + 1, r = row + 1; c < 8 && r < 8; ++c, ++r) {
        int new_pos = c * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check up left
    for (int c = col + 1, r = row - 1; c < 8 && r >= 0; ++c, --r) {
        int new_pos = c * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check down right
    for (int c = col - 1, r = row + 1; c >= 0 && r < 8; --c, ++r) {
        int new_pos = c * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }

    // check down left
    for (int c = col - 1, r = row - 1; c >= 0 && r >= 0; --c, --r) {
        int new_pos = c * 8 + r;
        if (!chessboard.chessboard.at(new_pos).has_piece()) {
            possible_moves.push_back(new_pos);
        } else if (piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
            possible_moves.push_back(new_pos);
            break;
        } else {
            break;
        }
    }
}

void test_knight(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int row = piece.pos % 8;
    int col = piece.pos / 8;
    // all possible moves
    int knight_moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int i = 0; i < 8; ++i) {
        int new_row = row + knight_moves[i][0];
        int new_col = col + knight_moves[i][1];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            int new_pos = new_col * 8 + new_row;
            if (!chessboard.chessboard.at(new_pos).has_piece() || piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
                possible_moves.push_back(new_pos);
            }
        }
    }
}

void test_queen(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    test_rook(piece, possible_moves, chessboard);
    test_bishop(piece, possible_moves, chessboard);
}

void test_king(const Piece &piece, std::vector<int> &possible_moves, const Chessboard &chessboard) {
    int row = piece.pos % 8;
    int col = piece.pos / 8;
    // all possible moves
    int king_moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (const auto &move : king_moves) {
        int new_row = row + move[0];
        int new_col = col + move[1];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            int new_pos = new_col * 8 + new_row;
            if (!chessboard.chessboard.at(new_pos).has_piece() ||
                piece.is_opposing_team(chessboard.chessboard.at(new_pos).piece)) {
                possible_moves.push_back(new_pos);
            }
        }
    }
}