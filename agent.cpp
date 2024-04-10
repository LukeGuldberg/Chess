#include "agent.h"

Agent::Agent(Chessboard initial_board)
{
    root = new Node(initial_board, std::pair<int, int>());
}

int Agent::minimax(Node *node, int depth, bool maximizingPlayer)
{
    if (depth == 0 || /* game is over */)
    {
        return evaluate(node->board_state);
    }

    if (maximizingPlayer)
    {
        int maxEval = INT_MIN;
        for (Node *child : node->children)
        {
            int eval = minimax(child, depth - 1, false);
            maxEval = max(maxEval, eval);
        }
        return maxEval;
    }
    else
    {
        int minEval = INT_MAX;
        for (Node *child : node->children)
        {
            int eval = minimax(child, depth - 1, true);
            minEval = min(minEval, eval);
        }
        return minEval;
    }
}

std::pair<int, int> Agent::find_best_move(int depth)
{
    // Generate the tree of game states up to the specified depth
    generate_tree(root, depth);

    int best_score = INT_MIN;
    std::pair<int, int> best_move;

    // Use minimax to find the best move
    for (Node *child : root->children)
    {
        int score = minimax(child, depth - 1, false);
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
    if (depth == 0) // game is over
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
            std::vector<int> possible_moves = tile.piece->get_possible_moves(node->board_state);
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
    if (board_state.chessboard.at(move.second).piece)
    {
        board_state.taken_pieces.push_back(std::move(board_state.chessboard.at(move.second).piece.value()));
    }
    board_state.chessboard.at(move.second).piece.reset();
    board_state.chessboard.at(move.first).piece.swap(board_state.chessboard.at(move.second).piece);
    board_state.chessboard.at(move.second).piece->pos = move.second;
    board_state.chessboard.at(move.first).piece->pos = move.first;
}

int Agent::evaluate(Chessboard state)
{
    // Implement your evaluation function here
}