#include "agent.h"
#include <climits>

Node::Node(const Node &other)
    : board_state(other.board_state), move(other.move), score(other.score)
{
    // deep copy
    for (Node *child : other.children)
    {
        children.push_back(new Node(*child));
    }
}

Node &Node::operator=(const Node &other) // copy assignment
{
    if (this != &other)
    {
        // deep copy
        board_state = other.board_state;
        move = other.move;
        score = other.score;

        reset_tree_recursive();

        for (Node *child : other.children)
        {
            children.push_back(new Node(*child));
        }
    }
    return *this;
}

Agent::Agent(Chessboard initial_board)
{
    initialize_opening_moves();
    root = new Node(initial_board, std::pair<int, int>{0, 0});
}

void Agent::initialize_opening_moves()
{
    opening_moves.push_back({11, 27});
    opening_moves.push_back({12, 20});
    opening_moves.push_back({5, 26});
    opening_moves.push_back({1, 18});
}

int Agent::minimax(Node *node, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0 || is_terminal(node->board_state)) // || game is over
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

bool Agent::is_terminal(Chessboard chessboard)
{
    // check for checkmate or stalemate
}

std::pair<int, int> Agent::find_best_move(int depth)
{
    // Generate the tree of game states up to the specified depth
    bool b_team = true;
    generate_tree(root, depth, b_team);

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

void Agent::generate_tree(Node *node, int depth, bool b_team)
{
    if (depth == 0) // or game is over
    {
        return;
    }

    std::vector<std::pair<int, int>> possible_moves = generate_possible_moves(node, b_team);

    for (std::pair<int, int> move : possible_moves)
    {
        Chessboard nextState = apply_move(node->board_state, move);
        Node *child = new Node(nextState, move);
        generate_tree(child, depth - 1, !b_team);
        node->children.push_back(child);
    }
}

std::vector<std::pair<int, int>> Agent::generate_possible_moves(Node *node, bool b_team)
{
    std::vector<std::pair<int, int>> all_possible_moves;
    for (Tile tile : node->board_state.chessboard)
    {
        std::vector<int> possible_moves;
        if (b_team)
        {
            if (tile.has_piece() && !tile.piece->team_white)
            {
                possible_moves = tile.piece->get_possible_moves(node->board_state);
            }
        } else {
            if (tile.has_piece() && tile.piece->team_white)
            {
                possible_moves = tile.piece->get_possible_moves(node->board_state);
            }
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
            // score += total number of pieces attacking
            // score -= total number of pieces being attacked (weigh based on what the pieces are?)
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
    root->reset_tree_recursive();

    root = new Node(state, std::pair<int, int>());
}

void Node::reset_tree_recursive()
{
    for (auto &child : children)
    {
        if (!child)
        {
            return;
        }
        child->reset_tree_recursive();
    }
    delete this;
}