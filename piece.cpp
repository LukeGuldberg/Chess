#include "piece.h"
#include "chessboard.h"
#include <iostream>

Piece::Piece(std::string file_name, int pos, Type type, bool team_white)
    : file_name{file_name}, pos{pos}, type{type}, team_white{team_white} {}

Piece::Piece(const Piece &other)
    : file_name(other.file_name), pos(other.pos), type(other.type), team_white(other.team_white) {}

Piece &Piece::operator=(const Piece &other)
{
    file_name = other.file_name;
    pos = other.pos;
    type = other.type;
    team_white = other.team_white;
    return *this;
}

Piece::Piece(Piece &&other) noexcept
    : file_name(std::move(other.file_name)), pos(other.pos), type(other.type), team_white(other.team_white) {}

Piece &Piece::operator=(Piece &&other) noexcept
{
    std::swap(file_name, other.file_name);
    pos = other.pos;
    type = other.type;
    team_white = other.team_white;
    return *this;
}

std::vector<int> Piece::get_possible_moves(const Chessboard &chessboard)
{
    std::vector<int> possible_moves;
    possible_moves.push_back(pos);
    switch (type)
    {
    case PAWN:
        if (team_white)
        {
            test_white_pawn(possible_moves, chessboard);
        }
        else
        {
            test_black_pawn(possible_moves, chessboard);
        }
        break;

    case BISHOP:
        test_bishop(possible_moves, chessboard);
        break;

    case ROOK:
        test_rook(possible_moves, chessboard);
        break;

    case KNIGHT:
        test_knight(possible_moves, chessboard);
        break;

    case KING:
        test_king(possible_moves, chessboard);
        break;

    case QUEEN:
        test_queen(possible_moves, chessboard);
        break;
    }
    return possible_moves;
}

bool Piece::is_opposing_team(const std::optional<Piece> other)
{
    if (!other)
    { // if other doesn't exist
        return false;
    }
    return team_white == other->team_white;
}

void Piece::test_white_pawn(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int forward_one = pos - 8;
    int forward_two = pos - 16;

    // Check one square forward
    if (!chessboard.chessboard.at(forward_one).has_piece())
    {
        possible_moves.push_back(forward_one);

        // Check two squares forward from starting position
        if ((pos < 56 && pos > 47) && !chessboard.chessboard.at(forward_two).has_piece())
        {
            possible_moves.push_back(forward_two);
        }
    }

    // Check diagonal left attacking move
    int left_attack = pos - 9;
    if (pos % 8 != 0 && is_opposing_team(chessboard.chessboard.at(left_attack).piece))
    {
        possible_moves.push_back(left_attack);
    }

    // Check diagonal right attacking move
    int right_attack = pos - 7;
    if (pos % 8 != 7 && is_opposing_team(chessboard.chessboard.at(right_attack).piece))
    {
        possible_moves.push_back(right_attack);
    }
}

void Piece::test_black_pawn(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int forward_one = pos + 8;
    int forward_two = pos + 16;

    // Check one square forward
    if (!chessboard.chessboard.at(forward_one).has_piece())
    {
        possible_moves.push_back(forward_one);

        // Check two squares forward from starting position
        if ((pos < 16 && pos > 7) && !chessboard.chessboard.at(forward_two).has_piece())
        {
            possible_moves.push_back(forward_two);
        }
    }

    // Check diagonal left attacking move
    int left_attack = pos + 7;
    if (pos % 8 != 0 && is_opposing_team(chessboard.chessboard.at(left_attack).piece))
    {
        possible_moves.push_back(left_attack);
    }

    // Check diagonal right attacking move
    int right_attack = pos + 9;
    if (pos % 8 != 7 && is_opposing_team(chessboard.chessboard.at(right_attack).piece))
    {
        possible_moves.push_back(right_attack);
    }
}

void Piece::test_rook(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int file = pos % 8; // File of the current position
    int rank = pos / 8; // Rank of the current position

    // Check upward
    for (int r = rank + 1; r < 8; ++r)
    {
        int new_pos = r * 8 + file;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check downward
    for (int r = rank - 1; r >= 0; --r)
    {
        int new_pos = r * 8 + file;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check to the right
    for (int f = file + 1; f < 8; ++f)
    {
        int new_pos = rank * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check to the left
    for (int f = file - 1; f >= 0; --f)
    {
        int new_pos = rank * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }
}

void Piece::test_bishop(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int file = pos % 8; // File of the current position
    int rank = pos / 8; // Rank of the current position

    // Check upward-right
    for (int r = rank + 1, f = file + 1; r < 8 && f < 8; ++r, ++f)
    {
        int new_pos = r * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check upward-left
    for (int r = rank + 1, f = file - 1; r < 8 && f >= 0; ++r, --f)
    {
        int new_pos = r * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check downward-right
    for (int r = rank - 1, f = file + 1; r >= 0 && f < 8; --r, ++f)
    {
        int new_pos = r * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }

    // Check downward-left
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; --r, --f)
    {
        int new_pos = r * 8 + f;
        if (!chessboard.chessboard.at(new_pos).has_piece())
        {
            possible_moves.push_back(new_pos);
        }
        else if (!is_opposing_team(chessboard.chessboard.at(new_pos).piece))
        {
            possible_moves.push_back(new_pos);
            break;
        }
        else
        {
            break;
        }
    }
}

void Piece::test_knight(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int file = pos % 8; // File of the current position
    int rank = pos / 8; // Rank of the current position

    int knight_moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int i = 0; i < 8; ++i)
    {
        int new_file = file + knight_moves[i][0];
        int new_rank = rank + knight_moves[i][1];
        if (new_file >= 0 && new_file < 8 && new_rank >= 0 && new_rank < 8)
        {
            int new_pos = new_rank * 8 + new_file;
            if (!chessboard.chessboard.at(new_pos).has_piece() || !is_opposing_team(chessboard.chessboard.at(new_pos).piece))
            {
                possible_moves.push_back(new_pos);
            }
        }
    }
}

void Piece::test_queen(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    test_rook(possible_moves, chessboard);
    test_bishop(possible_moves, chessboard);
}

void Piece::test_king(std::vector<int> &possible_moves, const Chessboard &chessboard)
{
    int file = pos % 8; // File of the current position
    int rank = pos / 8; // Rank of the current position

    // Define possible king moves relative to its position
    int king_moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    // Iterate over possible king moves
    for (const auto &move : king_moves)
    {
        int new_file = file + move[0];
        int new_rank = rank + move[1];

        // Ensure the new position is within the board boundaries
        if (new_file >= 0 && new_file < 8 && new_rank >= 0 && new_rank < 8)
        {
            int new_pos = new_rank * 8 + new_file;

            // Check if the new position is empty or occupied by an opposing piece
            if (!chessboard.chessboard.at(new_pos).has_piece() ||
                !is_opposing_team(chessboard.chessboard.at(new_pos).piece))
            {
                possible_moves.push_back(new_pos);
            }
        }
    }
}