#include "agent.h"

Agent::Agent(Chessboard initial_board)
{
    initialize_opening_moves();
    root = new Node(initial_board, std::pair<int, int>());
}

void Agent::initialize_opening_moves(){
    opening_moves.push_back({11, 27});
    opening_moves.push_back({12, 20});
    opening_moves.push_back({5, 26});
    opening_moves.push_back({1, 18});
}

int Agent::minimax(Node *node, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0) // || game is over
    {
        return evaluate(node->board_state);
    }

    if (maximizingPlayer)
    {
        int maxEval = INT_MIN;
        for (Node *child : node->children)
        {
            int eval = minimax(child, depth - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha)
            {
                break; // Beta cutoff
            }
        }
        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        for (Node *child : node->children)
        {
            int eval = minimax(child, depth - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha)
            {
                break; // Alpha cutoff
            }
        }
        return minEval;
    }
}

int Agent::min(int a, int b)
{
    return (a < b) ? a : b;
}

int Agent::max(int a, int b)
{
    return (a > b) ? a : b;
}

std::pair<int, int> Agent::find_best_move(int depth)
{
    // Generate the tree of game states up to the specified depth
    generate_tree(root, depth);

    int best_score = INT_MIN;
    std::pair<int, int> best_move;

    int alpha = INT_MIN;
    int beta = INT_MAX;

    // Use minimax to find the best move
    for (Node *child : root->children)
    {
        int score = minimax(child, depth - 1, alpha, beta, false);
        if (score > best_score)
        {
            best_score = score;
            best_move = child->move;
        }
    }

    return best_move;
}

void Agent::generate_tree(Node *node, int depth)
{
    if (depth == 0) // or game is over
    {
        return;
    }

    std::vector<std::pair<int, int>> possible_moves = generate_possible_moves(node);

    for (std::pair<int, int> move : possible_moves)
    {
        Chessboard nextState = apply_move(node->board_state, move);
        Node *child = new Node(nextState, move);
        generate_tree(child, depth - 1);
        node->children.push_back(child);
    }
}

std::vector<std::pair<int, int>> Agent::generate_possible_moves(Node *node)
{
    std::vector<std::pair<int, int>> all_possible_moves;
    for (Tile tile : node->board_state.chessboard)
    {
        std::vector<int> possible_moves;
        if (tile.has_piece())
        {
            possible_moves = tile.piece->get_possible_moves(node->board_state);
        }
        for (int i : possible_moves)
        {
            all_possible_moves.push_back({tile.piece->pos, i});
        }
    }
    return all_possible_moves;
}

Chessboard Agent::apply_move(Chessboard board_state, std::pair<int, int> move)
{
    Chessboard new_board_state = board_state;
    if (board_state.chessboard.at(move.second).piece)
    {
        board_state.taken_pieces.push_back(std::move(board_state.chessboard.at(move.second).piece.value()));
    }
    board_state.chessboard.at(move.second).piece.reset();
    board_state.chessboard.at(move.first).piece.swap(board_state.chessboard.at(move.second).piece);
    board_state.chessboard.at(move.second).piece->pos = move.second;
    board_state.chessboard.at(move.first).piece->pos = move.first;
    return board_state;
}

int Agent::evaluate(Chessboard state)
{
    int score = 0;
    // Implement your evaluation function here
    for (auto &tile : state.chessboard)
    {
        if (tile.piece)
        {
            score += get_piece_value(tile.piece->type);            // overall piece score comparison
            score += tile.piece->get_possible_moves(state).size(); // includes mobility into the score comparison
        }
    }
    if (state.white_to_move)
    {
        score *= -1;
    }
    return score;
}

int Agent::get_piece_value(Type type)
{
    switch (type)
    {
    case PAWN:
        return pawn_value;
    case BISHOP:
        return bishop_value;
    case ROOK:
        return rook_value;
    case KNIGHT:
        return knight_value;
    case QUEEN:
        return queen_value;
    case KING:
        return king_value;
    }
    return 0;
}

void Agent::reset_tree(Chessboard state)
{
    reset_tree_recursive(root);

    root = new Node(state, std::pair<int, int>());
}

void Agent::reset_tree_recursive(Node* node) {
    if (!node)
        return;
    for (auto &child : node->children)
    {
        reset_tree_recursive(child);
    }
    delete node;
}