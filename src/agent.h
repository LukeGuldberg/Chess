#include "chessboard.h"
#include <vector>

class Node
{
public:
    Node(Chessboard state, std::pair<int, int> move) : board_state(state), move(move), score(0) {}
    Node(const Node &other);
    Node &operator=(const Node &other);

    void reset_tree_recursive();

    Chessboard board_state;
    std::pair<int, int> move;
    int score;
    std::vector<Node *> children;

private:
    Node(Node &&other) = delete;
    Node &operator=(Node &&other) = delete;
};

class Agent
{
public:
    Agent(Chessboard initial_board);
    void initialize_opening_moves();

    Node *root;

    std::vector<std::pair<int, int>> opening_moves;

    // int minimax(Node *node, int depth, bool maximizingPlayer);
    int minimax(Node *node, int depth, int alpha, int beta, bool maximizingPlayer);
    int min(int a, int b);
    int max(int a, int b);

    bool is_terminal(Chessboard chessboard);

    std::pair<int, int> find_best_move(int depth);
    Chessboard apply_move(Chessboard board_state, std::pair<int, int> move);
    void generate_tree(Node *node, int depth, bool b_team);
    std::vector<std::pair<int, int>> generate_possible_moves(Node *node, bool b_team);

    void reset_tree(Chessboard state);
    void reset_tree_recursive(Node *node);

    int evaluate(Chessboard state);
    int get_piece_value(Type type);

private:
    int pawn_value = 1;
    int knight_value = 3;
    int bishop_value = 3;
    int rook_value = 5;
    int queen_value = 9;
    int king_value = 10;

    Agent(const Agent &other) = delete;
    Agent &operator=(const Agent &other) = delete;
    Agent(Agent &&other) = delete;
    Agent &operator=(Agent &&other) = delete;
};
