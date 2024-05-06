#include <catch2/catch_test_macros.hpp>
#include "chessboard.h"
#include "piece.h"
#include <vector>

TEST_CASE("Move pieces on Chessboard", "[Chessboard]")
{
    Chessboard board;

    SECTION("Move pawn to a valid position")
    {
        board.move_piece(48, 40);
        REQUIRE(board.chessboard.at(40).has_piece() == true);
    }

    SECTION("Attempt to move pawn to an invalid position")
    {
        board.move_piece(49, 16);
        REQUIRE(board.chessboard.at(16).has_piece() == false);
    }

    SECTION("Confirm the possible moves for a pawn")
    {
        std::vector<int> possible_moves = board.chessboard.at(55).piece->get_possible_moves(board);
        REQUIRE(possible_moves.at(0) == 55);
        REQUIRE(possible_moves.at(1) == 47);
        REQUIRE(possible_moves.at(2) == 39);
    }

    SECTION("Confirm two pieces are on the same team")
    {
        REQUIRE(board.chessboard.at(59).piece->is_opposing_team(board.chessboard.at(3).piece) == true);
    }

    SECTION("Confirm two pieces are on different teams")
    {
        REQUIRE(board.chessboard.at(59).piece->is_opposing_team(board.chessboard.at(60).piece) == false);
    }

    
}
