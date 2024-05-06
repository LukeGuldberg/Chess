/**
 * @file agent.cpp
 * @brief How the Agent finds its move.
 *
 * The agent files are used to produce the best move for the black team. Finding the best move requires looking at how a move affects mobility, structuring of pieces, and whether or not you take or lose pieces. This is all calculated in the function evaluate(). This function is called on every move that the minimax algorithm (with alpha beta pruning) passes it. The minimax algorithm is used to allow the agent to search X moves ahead and figure out which produces the best possible outcome for itself, and the worst possible outcome for the other player. Each move/new gamestate is represented within a Node, and each Node hold a vector of other Nodes.
 *
 */
#include "agent.h"

#include <climits>

Agent::Agent(Chessboard initial_board) {
    initialize_piece_structure_bonus();  // set all values of the piece structure vectors
    root = new Node(initial_board, std::pair<int, int>{0, 0});

    int pawn_value = 100;
    int knight_value = 310;
    int bishop_value = 320;
    int rook_value = 500;
    int queen_value = 900;
    int king_value = 1500;
    piece_values = {pawn_value, knight_value, bishop_value, rook_value, king_value, queen_value};
}

void Agent::initialize_piece_structure_bonus() {
    piece_structures.push_back(pawn_structure_black = {
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   5, 10, 10, -20, -20, 10, 10, 5,
                                   5, -5, -10, 0, 0, -10, -5, 5,
                                   0, 0, 0, 30, 30, 0, 0, 0,
                                   5, 5, 10, 25, 25, 10, 5, 5,
                                   10, 10, 20, 30, 30, 20, 10, 10,
                                   50, 50, 50, 50, 50, 50, 50, 50,
                                   0, 0, 0, 0, 0, 0, 0, 0});

    piece_structures.push_back(knight_structure_black = {
                                   -50, -40, -30, -30, -30, -30, -40, -50,
                                   -40, -20, 0, 5, 5, 0, -20, -40,
                                   -30, 5, 10, 15, 15, 10, 5, -30,
                                   -30, 0, 15, 20, 20, 15, 0, -30,
                                   -30, 5, 15, 20, 20, 15, 5, -30,
                                   -30, 0, 10, 15, 15, 10, 0, -30,
                                   -40, -20, 0, 0, 0, 0, -20, -40,
                                   -50, -40, -30, -30, -30, -30, -40, -50});

    piece_structures.push_back(bishop_structure_black = {
                                   0, 0, 0, 5, 5, 0, 0, 0,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   5, 10, 10, 10, 10, 10, 10, 5,
                                   0, 0, 0, 0, 0, 0, 0, 0});

    piece_structures.push_back(rook_structure_black = {
                                   0, 0, 0, 5, 5, 0, 0, 0,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   5, 10, 10, 10, 10, 10, 10, 5,
                                   0, 0, 0, 0, 0, 0, 0, 0});

    piece_structures.push_back(king_structure_black = {
                                   20, 30, 10, 0, 0, 10, 30, 20,
                                   20, 20, 0, 0, 0, 0, 20, 20,
                                   -10, -20, -20, -20, -20, -20, -20, -10,
                                   -20, -30, -30, -40, -40, -30, -30, -20,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30});

    piece_structures.push_back(end_king_structure_black = {
                                   -50, -30, -30, -30, -30, -30, -30, -50,
                                   -30, -30, 0, 0, 0, 0, -30, -30,
                                   -30, -10, 20, 30, 30, 20, -10, -30,
                                   -30, -10, 30, 40, 40, 30, -10, -30,
                                   -30, -10, 30, 40, 40, 30, -10, -30,
                                   -30, -10, 20, 30, 30, 20, -10, -30,
                                   -30, -20, -10, 0, 0, -10, -20, -30,
                                   -50, -40, -30, -20, -20, -30, -40, -50});

    piece_structures.push_back(queen_structure_black = {
                                   -20, -10, -10, -5, -5, -10, -10, -20,
                                   -10, 0, 5, 0, 0, 0, 0, -10,
                                   -10, 5, 5, 5, 5, 5, 0, -10,
                                   0, 0, 5, 5, 5, 5, 0, -5,
                                   -5, 0, 5, 5, 5, 5, 0, -5,
                                   -10, 0, 5, 5, 5, 5, 0, -10,
                                   -10, 0, 0, 0, 0, 0, 0, -10,
                                   -20, -10, -10, -5, -5, -10, -10, -20});

    piece_structures.push_back(pawn_structure_white = {
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   50, 50, 50, 50, 50, 50, 50, 50,
                                   10, 10, 20, 30, 30, 20, 10, 10,
                                   5, 5, 10, 25, 25, 10, 5, 5,
                                   0, 0, 0, 20, 20, 0, 0, 0,
                                   5, -5, -10, 0, 0, -10, -5, 5,
                                   5, 10, 10, -20, -20, 10, 10, 5,
                                   0, 0, 0, 0, 0, 0, 0, 0});

    piece_structures.push_back(knight_structure_white = {
                                   -50, -40, -30, -30, -30, -30, -40, -50,
                                   -40, -20, 0, 0, 0, 0, -20, -40,
                                   -30, 0, 10, 15, 15, 10, 0, -30,
                                   -30, 5, 15, 20, 20, 15, 5, -30,
                                   -30, 0, 15, 20, 20, 15, 0, -30,
                                   -30, 5, 10, 15, 15, 10, 5, -30,
                                   -40, -20, 0, 5, 5, 0, -20, -40,
                                   -50, -40, -30, -30, -30, -30, -40, -50});

    piece_structures.push_back(bishop_structure_white = {
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   5, 10, 10, 10, 10, 10, 10, 5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   0, 0, 0, 5, 5, 0, 0, 0});

    piece_structures.push_back(rook_structure_white = {
                                   0, 0, 0, 0, 0, 0, 0, 0,
                                   5, 10, 10, 10, 10, 10, 10, 5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   -5, 0, 0, 0, 0, 0, 0, -5,
                                   0, 0, 0, 5, 5, 0, 0, 0});

    piece_structures.push_back(king_structure_white = {
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -30, -40, -40, -50, -50, -40, -40, -30,
                                   -20, -30, -30, -40, -40, -30, -30, -20,
                                   -10, -20, -20, -20, -20, -20, -20, -10,
                                   20, 20, 0, 0, 0, 0, 20, 20,
                                   20, 30, 10, 0, 0, 10, 30, 20});

    piece_structures.push_back(end_king_structure_white = {
                                   -50, -40, -30, -20, -20, -30, -40, -50,
                                   -30, -20, -10, 0, 0, -10, -20, -30,
                                   -30, -10, 20, 30, 30, 20, -10, -30,
                                   -30, -10, 30, 40, 40, 30, -10, -30,
                                   -30, -10, 30, 40, 40, 30, -10, -30,
                                   -30, -10, 20, 30, 30, 20, -10, -30,
                                   -30, -30, 0, 0, 0, 0, -30, -30,
                                   -50, -30, -30, -30, -30, -30, -30, -50});

    piece_structures.push_back(queen_structure_white = {
                                   -20, -10, -10, -5, -5, -10, -10, -20,
                                   -10, 0, 0, 0, 0, 0, 0, -10,
                                   -10, 0, 5, 5, 5, 5, 0, -10,
                                   -5, 0, 5, 5, 5, 5, 0, -5,
                                   0, 0, 5, 5, 5, 5, 0, -5,
                                   -10, 5, 5, 5, 5, 5, 0, -10,
                                   -10, 0, 5, 0, 0, 0, 0, -10,
                                   -20, -10, -10, -5, -5, -10, -10, -20});
}

int Agent::minimax(Node *node, int depth, int alpha, int beta, bool maximizingPlayer) {
    // recursively traverse the tree of moves calculating the score for each,
    // then returning either the best or worst score depending on whose move it is
    if (depth == 0) {
        return evaluate(node->board_state);
    }

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (Node *child : node->children) {
            int eval = minimax(child, depth - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;  // Beta cutoff
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (Node *child : node->children) {
            int eval = minimax(child, depth - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break;  // Alpha cutoff
            }
        }
        return minEval;
    }
}

int Agent::min(int a, int b) { return (a < b) ? a : b; }

int Agent::max(int a, int b) { return (a > b) ? a : b; }

std::pair<int, int> Agent::find_best_move(int depth) {
    // Generate the tree of game states up to the specified depth
    bool b_team = true;
    generate_tree(root, depth, b_team);

    int best_score = INT_MIN;
    std::pair<int, int> best_move;

    int alpha = INT_MIN;
    int beta = INT_MAX;

    // Use minimax to find the best move
    for (Node *child : root->children) {
        int score = minimax(child, depth - 1, alpha, beta, false);
        if (score > best_score && root->board_state.is_valid_move(child->move.first, child->move.second)) {
            best_score = score;
            best_move = child->move;
        }
    }
    return best_move;  // best move can't be the same position twice, that
                       // causes a bug that makes pieces disappear
}

void Agent::generate_tree(Node *node, int depth, bool b_team) {
    if (depth == 0) {
        return;
    }
    std::vector<std::pair<int, int>> possible_moves = generate_possible_moves(node, b_team);
    for (std::pair<int, int> move : possible_moves) {
        if (node->board_state.is_valid_move(move.first, move.second)) {
            Chessboard nextState = node->board_state;  // make copy for the next child
            if (nextState.move_piece(move.first, move.second)) {
                // if the move was valid
                Node *child = new Node(nextState, move);
                generate_tree(child, depth - 1, !b_team);
                node->children.push_back(child);
            }
        }
    }
}

std::vector<std::pair<int, int>> Agent::generate_possible_moves(Node *node, bool b_team) {
    std::vector<std::pair<int, int>> all_possible_moves;
    for (Tile tile : node->board_state.chessboard) {
        std::vector<int> possible_moves;
        if (b_team) {
            if (tile.has_piece() && !tile.piece->team_white) {
                possible_moves =
                    tile.piece->get_possible_moves(node->board_state);
            }
        } else {
            if (tile.has_piece() && tile.piece->team_white) {
                possible_moves =
                    tile.piece->get_possible_moves(node->board_state);
            }
        }
        for (int i : possible_moves) {
            all_possible_moves.push_back({tile.piece->pos, i});
        }
    }
    return all_possible_moves;
}

int Agent::evaluate(Chessboard state) {
    // calculates a given game state based on all piece values, the mobility of said pieces, and the structure of their formation
    if (state.w_num_pieces < 5) {
        king_structure_white = end_king_structure_white;
    }
    if (state.b_num_pieces < 5) {
        king_structure_black = end_king_structure_black;
    }
    int score = 0;

    for (auto &tile : state.chessboard) {
        if (tile.piece) {
            int pieceValue = get_piece_value(tile.piece->type);  // Piece values
            score += (tile.piece->team_white ? -pieceValue : pieceValue);

            std::vector<int> possibleMoves = tile.piece->get_possible_moves(state);  // Mobility
            score += possibleMoves.size() * (tile.piece->team_white ? -1 : 1);

            if (tile.piece->team_white) {  // Piece structure
                score -= get_piece_structure(tile.piece.value()).at(tile.piece->pos);
            } else {
                score += get_piece_structure(tile.piece.value()).at(tile.piece->pos);
            }
        }
    }

    return score;
}
std::vector<int> Agent::get_piece_structure(Piece piece) {  // piece structure constant time lookup
    return piece_structures.at(piece.type + piece.team_white * 6);
}

int Agent::get_piece_value(Type type) {
    return piece_values.at(type);
}

void Agent::reset_tree(Chessboard state) {
    root->reset_tree_recursive();

    root = new Node(state, std::pair<int, int>());
}

void Node::reset_tree_recursive() {
    for (auto &child : children) {
        if (!child) {
            return;
        }
        child->reset_tree_recursive();
    }
    delete this;
}