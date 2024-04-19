#include <vector>

#include "chessboard.h"

class Node {
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

class Agent {
   public:
    Agent(Chessboard initial_board);
    void initialize_opening_moves();
    void initialize_piece_structure_bonus();

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
    int pawn_structure_bonus_white(int pawnPos);
    int pawn_structure_bonus_black(int pawnPos);
    std::vector<int> get_piece_structure(Piece piece);
    int get_piece_value(Type type);

   private:
    std::vector<int> piece_values;

    std::vector<std::vector<int>> piece_structures;
    std::vector<int> pawn_structure_white;
    std::vector<int> pawn_structure_black;
    std::vector<int> knight_structure_white;
    std::vector<int> knight_structure_black;
    std::vector<int> bishop_structure_white;
    std::vector<int> bishop_structure_black;
    std::vector<int> rook_structure_white;
    std::vector<int> rook_structure_black;
    std::vector<int> king_structure_white;
    std::vector<int> king_structure_black;
    std::vector<int> queen_structure_white;
    std::vector<int> queen_structure_black;

    Agent(const Agent &other) = delete;
    Agent &operator=(const Agent &other) = delete;
    Agent(Agent &&other) = delete;
    Agent &operator=(Agent &&other) = delete;
};
