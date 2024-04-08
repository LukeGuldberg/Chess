#include "agent.h"

Agent::Agent(Chessboard initial_board)
{
    root = new Node(initial_board, NULL);
}

int Agent::minimax(Node *node, int depth, bool maximizingPlayer)
{
    if (depth == 0 || /* game is over */)
    {
        return evaluate(node->state);
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
    if (depth == 0 || /* game is over */)
    {
        return;
    }

    std::vector<std::pair<int, int>> possible_moves = node->board_state generate_possible_moves(node->board_state);

    for (std::pair<int, int> move : possible_moves)
    {
        Chessboard nextState = apply_move(node->board_state, move);
        Node *child = new Node(nextState, move);
        generate_tree(child, depth - 1);
        node->children.push_back(child);
    }
}

int Agent::evaluate(Chessboard state)
{
    // Implement your evaluation function here
}