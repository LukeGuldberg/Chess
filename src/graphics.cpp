#include "graphics.h"
#include "chessboard.h"
#include "piece.h"

#include <SDL_image.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

Graphics::Graphics(const std::string &title)
{
    initialize_graphics(title);
    load_sprites();
}

Graphics::Graphics(Graphics &&other)
    : renderer{other.renderer},
      selected_tile{other.selected_tile},
      previous_move{other.previous_move},
      possible_moves{other.possible_moves},
      window{other.window},
      dark_square_texture{other.dark_square_texture},
      light_square_texture{other.light_square_texture},
      w_pawn_texture{other.w_pawn_texture},
      w_bishop_texture{other.w_bishop_texture},
      w_rook_texture{other.w_rook_texture},
      w_knight_texture{other.w_knight_texture},
      w_king_texture{other.w_king_texture},
      w_queen_texture{other.w_queen_texture},
      b_pawn_texture{other.b_pawn_texture},
      b_bishop_texture{other.b_bishop_texture},
      b_rook_texture{other.b_rook_texture},
      b_knight_texture{other.b_knight_texture},
      b_king_texture{other.b_knight_texture},
      b_queen_texture{other.b_queen_texture}
{
    other.renderer = nullptr;
    other.window = nullptr;
    other.dark_square_texture = nullptr;
    other.light_square_texture = nullptr;
    other.b_pawn_texture = nullptr;
    other.b_bishop_texture = nullptr;
    other.b_knight_texture = nullptr;
    other.b_rook_texture = nullptr;
    other.b_king_texture = nullptr;
    other.b_queen_texture = nullptr;
}

Graphics &Graphics::operator=(Graphics &&rhs)
{
    std::swap(renderer, rhs.renderer);
    std::swap(window, rhs.window);

    return *this;
}

Graphics::~Graphics()
{ // clean up: release SDL resources
    destroy_textures();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Graphics::destroy_textures()
{
    SDL_DestroyTexture(light_square_texture);
    SDL_DestroyTexture(dark_square_texture);

    SDL_DestroyTexture(w_pawn_texture);
    SDL_DestroyTexture(w_bishop_texture);
    SDL_DestroyTexture(w_knight_texture);
    SDL_DestroyTexture(w_rook_texture);
    SDL_DestroyTexture(w_king_texture);
    SDL_DestroyTexture(w_queen_texture);

    SDL_DestroyTexture(b_pawn_texture);
    SDL_DestroyTexture(b_bishop_texture);
    SDL_DestroyTexture(b_knight_texture);
    SDL_DestroyTexture(b_rook_texture);
    SDL_DestroyTexture(b_king_texture);
    SDL_DestroyTexture(b_queen_texture);
}

void Graphics::clear()
{ // clear the screen by painting it black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::update()
{
    SDL_RenderPresent(renderer);
}

void Graphics::initialize_graphics(const std::string title)
{
    int result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0)
    {
        std::cout << SDL_GetError() << "\n";
    }
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen_width, screen_height, 0);
    if (!window)
    {
        std::cout << SDL_GetError() << "\n";
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // initialize SDL, create a window and renderer
    // make sure to check all return values and throw exceptions when errors occur

    if (!renderer)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // SDL2 image
    int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags) & img_flags))
    {
        throw std::runtime_error(IMG_GetError());
    }
}
void Graphics::load_sprites()
{
    dark_square_texture = loadTexture(renderer, "../assets/dark_square.xcf");
    light_square_texture = loadTexture(renderer, "../assets/light_square.xcf");

    // w_pawn_texture = loadTexture(renderer, "../assets/w_pawn.xcf");
    // w_bishop_texture = loadTexture(renderer, "../assets/w_bishop.xcf");
    // w_knight_texture = loadTexture(renderer, "../assets/w_knight.xcf");
    // w_rook_texture = loadTexture(renderer, "../assets/w_rook.xcf");
    // w_king_texture = loadTexture(renderer, "../assets/w_king.xcf");
    // w_queen_texture = loadTexture(renderer, "../assets/w_queen.xcf");

    // b_pawn_texture = loadTexture(renderer, "../assets/b_pawn.xcf");
    // b_bishop_texture = loadTexture(renderer, "../assets/b_bishop.xcf");
    // b_knight_texture = loadTexture(renderer, "../assets/b_knight.xcf");
    // b_rook_texture = loadTexture(renderer, "../assets/b_rook.xcf");
    // b_king_texture = loadTexture(renderer, "../assets/b_king.xcf");
    // b_queen_texture = loadTexture(renderer, "../assets/b_queen.xcf");

    sdl_textures.push_back(loadTexture(renderer, "../assets/b_pawn.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/b_knight.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/b_bishop.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/b_rook.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/b_king.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/b_queen.xcf"));

    sdl_textures.push_back(loadTexture(renderer, "../assets/w_pawn.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/w_knight.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/w_bishop.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/w_rook.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/w_king.xcf"));
    sdl_textures.push_back(loadTexture(renderer, "../assets/w_queen.xcf"));
}

SDL_Texture *Graphics::find_texture(std::optional<Piece> piece)
{
    return sdl_textures.at(piece->type + piece->team_white * 6);

    // switch (piece->type)
    // {
    // case PAWN:
    //     if (piece->team_white)
    //     {
    //         return w_pawn_texture;
    //     }
    //     else
    //     {
    //         return b_pawn_texture;
    //     }
    //     break;
    // case BISHOP:
    //     if (piece->team_white)
    //     {
    //         return w_bishop_texture;
    //     }
    //     else
    //     {
    //         return b_bishop_texture;
    //     }
    //     break;
    // case ROOK:
    //     if (piece->team_white)
    //     {
    //         return w_rook_texture;
    //     }
    //     else
    //     {
    //         return b_rook_texture;
    //     }
    //     break;
    // case KNIGHT:
    //     if (piece->team_white)
    //     {
    //         return w_knight_texture;
    //     }
    //     else
    //     {
    //         return b_knight_texture;
    //     }
    //     break;
    // case KING:
    //     if (piece->team_white)
    //     {
    //         return w_king_texture;
    //     }
    //     else
    //     {
    //         return b_king_texture;
    //     }
    //     break;
    // case QUEEN:
    //     if (piece->team_white)
    //     {
    //         return w_queen_texture;
    //     }
    //     else
    //     {
    //         return b_queen_texture;
    //     }
    //     break;
    // }
    // return nullptr;
}

void Graphics::draw_background()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 152, 118, 84, 255);
    SDL_Rect rectPos = {0, 0, screen_width, screen_height};
    SDL_RenderFillRect(renderer, &rectPos);
}
void Graphics::draw_board()
{
    if (!dark_square_texture || !light_square_texture)
    { // Handle loading error
        std::cerr << "Failed to load texture(s) for board squares!" << std::endl;
        return;
    }

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            SDL_Rect rectPos = {col * tile_size + left_bound, row * tile_size + upper_bound, tile_size, tile_size};
            if ((row + col) % 2 == 0)
            {
                draw_sprite(light_square_texture, rectPos);
            }
            else
            {
                draw_sprite(dark_square_texture, rectPos);
            }
        }
    }
}

void Graphics::draw_pieces(Chessboard &chessboard)
{
    for (const Tile &t : chessboard.chessboard)
    {
        if (t.piece)
        {
            std::pair<int, int> pos = chessboard.board_to_pixel(t.piece->pos, *this);
            SDL_Rect rectPos = {pos.first, pos.second, tile_size, tile_size};
            draw_sprite(find_texture(t.piece), rectPos);
        }
    }
}

void Graphics::draw_taken_pieces(Chessboard &chessboard)
{
    for (const Piece &t : chessboard.taken_pieces)
    {
        // this is a nice to have
    }
}

void Graphics::draw_sprite(SDL_Texture *spriteTexture, SDL_Rect rectPos)
{
    SDL_RenderCopy(renderer, spriteTexture, NULL, &rectPos);
}

SDL_Texture *Graphics::loadTexture(SDL_Renderer *renderer, const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Unable to load image '" << path << "'! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Graphics::highlight_tiles(const Chessboard &chessboard, const Graphics &graphics)
{
    highlight_selected_tile(chessboard, graphics);
    highlight_previous_move(chessboard, graphics);
    if (show_possible_moves)
    {
        highlight_possible_moves(chessboard, graphics);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Graphics::highlight_selected_tile(const Chessboard &chessboard, const Graphics &graphics)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
    if (selected_tile != -1)
    {
        auto position = chessboard.board_to_pixel(selected_tile, graphics);
        SDL_Rect rectPos = {position.first, position.second, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &rectPos);
    }
}

void Graphics::highlight_previous_move(const Chessboard &chessboard, const Graphics &graphics)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 100);
    for (const int &pos : previous_move)
    {
        if (pos == -1)
        {
            break;
        }
        auto position = chessboard.board_to_pixel(pos, graphics);
        SDL_Rect rectPos = {position.first, position.second, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &rectPos);
    }
}
void Graphics::highlight_possible_moves(const Chessboard &chessboard, const Graphics &graphics)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
    for (const int &pos : possible_moves)
    {
        if (pos == -1)
        {
            break;
        }
        auto position = chessboard.board_to_pixel(pos, graphics);
        SDL_Rect rectPos = {position.first, position.second, tile_size, tile_size};
        SDL_RenderFillRect(renderer, &rectPos);
    }
}
