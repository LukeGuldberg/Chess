#include "piece.h"

Piece::Piece(std::string file_name, int pos, Type type, bool team_white)
    : file_name{file_name}, pos{pos}, type{type}, team_white{team_white} {}

std::vector<int> Piece::get_possible_moves(const Chessboard &chessboard)
{
    std::vector<int> possible_moves;
    possible_moves.push_back(pos);
    if (team_white)
    {
        switch (type)
        {
        case PAWN:
            possible_moves.push_back(pos - 8);
            possible_moves.push_back(pos - 16);
            break;

        case BISHOP:
            break;

        case ROOK:
            break;

        case KNIGHT:
            break;

        case KING:
            break;

        case QUEEN:
            break;
        }
    }
    else
    {

        switch (type)
        {
        case PAWN:
            possible_moves.push_back(pos + 8);
            possible_moves.push_back(pos + 16);
            break;

        case BISHOP:
            break;

        case ROOK:
            break;

        case KNIGHT:
            break;

        case KING:
            break;

        case QUEEN:
            break;
        }
    }
    return possible_moves;
}

bool Piece::is_opposing_team(const Piece &other)
{
    return team_white == other.team_white;
}