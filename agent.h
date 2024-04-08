#include "chessboard.h"
#include <vector>


class Node
{
public:
    Node(Chessboard state, std::pair<int, int> move) : board_state(board_state), move(move), score(0) {}
    Chessboard board_state;
    std::pair<int, int> move;
    int score;
    std::vector<Node *> children;    
};

class Agent
{
public:
    Agent(Chessboard initial_board);

    Node *root;

    int minimax(Node *node, int depth, bool maximizingPlayer);
    std::pair<int, int> find_best_move(int depth);

    void generate_tree(Node *node, int depth);

    int evaluate(Chessboard state);
};
