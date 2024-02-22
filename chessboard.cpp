#include "chessboard.h"
#include <string>

Chessboard::Chessboard()
{
    fill_starting_tiles();
    place_starting_b_pieces();
    place_starting_w_pieces();
    // create all tiles
}

int Chessboard::pixel_to_board(int x, int y)
{
    int index_y = ((y - 86) / 91) * 8;
    int index_x = (x - 436) / 91;
    return index_x + index_y;
}

std::pair<int, int> Chessboard::board_to_pixel(int i)
{
    int x = i % 8;
    int y = i / 8;

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
    // SDL_Texture *black_pawn = graphics.loadTexture(graphics->renderer, "b_pawn.png");
    // SDL_Texture *black_rook = graphics.loadTexture(graphics->renderer, "w_rook.png");
    // SDL_Texture *black_knight = graphics.loadTexture(graphics->renderer, "b_knight.png");
    // SDL_Texture *black_bishop = graphics.loadTexture(graphics->renderer, "b_bishop.png");
    // SDL_Texture *black_queen = graphics.loadTexture(graphics->renderer, "b_queen.png");
    // SDL_Texture *black_king = graphics.loadTexture(graphics->renderer, "b_king.png");

    chessboard.push_back(Tile{Piece{"w_rook.png", 0, ROOK}});
    chessboard.push_back(Tile{Piece{"b_knight.png", 1, KNIGHT}});
    chessboard.push_back(Tile{Piece{"b_bishop.png", 2, BISHOP}});
    chessboard.push_back(Tile{Piece{"b_queen.png", 3, QUEEN}});
    chessboard.push_back(Tile{Piece{"b_king.png", 4, KING}});
    chessboard.push_back(Tile{Piece{"b_bishop.png", 5, BISHOP}});
    chessboard.push_back(Tile{Piece{"b_knight.png", 6, KNIGHT}});
    chessboard.push_back(Tile{Piece{"w_rook.png", 7, ROOK}});

    for (int i = 8; i < 16; ++i)
    {
        chessboard.push_back(Tile{Piece{"b_pawn.png", i, PAWN}});
    }
}

void Chessboard::place_starting_w_pieces()
{
    // SDL_Texture *white_pawn = graphics.loadTexture(graphics->renderer, "w_pawn.png");
    // SDL_Texture *white_rook = graphics.loadTexture(graphics->renderer, "w_rook.png");
    // SDL_Texture *white_knight = graphics.loadTexture(graphics->renderer, "w_knight.png");
    // SDL_Texture *white_bishop = graphics.loadTexture(graphics->renderer, "w_bishop.png");
    // SDL_Texture *white_queen = graphics.loadTexture(graphics->renderer, "w_queen.png");
    // SDL_Texture *white_king = graphics.loadTexture(graphics->renderer, "w_king.png");

    chessboard.push_back(Tile{Piece{"w_rook.png", 56, ROOK}});
    chessboard.push_back(Tile{Piece{"w_knight.png", 57, KNIGHT}});
    chessboard.push_back(Tile{Piece{"w_bishop.png", 58, BISHOP}});
    chessboard.push_back(Tile{Piece{"w_queen.png", 59, QUEEN}});
    chessboard.push_back(Tile{Piece{"w_king.png", 60, KING}});
    chessboard.push_back(Tile{Piece{"w_bishop.png", 61, BISHOP}});
    chessboard.push_back(Tile{Piece{"w_knight.png", 62, KNIGHT}});
    chessboard.push_back(Tile{Piece{"w_rook.png", 63, ROOK}});

    for (int i = 48; i < 56; ++i)
    {
        chessboard.push_back(Tile{Piece{"w_pawn.png", i, PAWN}});
    }
}
