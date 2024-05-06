/**
 * @file agent.h
 * @brief How the Agent finds its move.
 *
 * The agent files are used to produce the best move for the black team. Finding the best move requires looking at how a move affects mobility, structuring of pieces, and whether or not you take or lose pieces. This is all calculated in the function evaluate(). This function is called on every move that the minimax algorithm (with alpha beta pruning) passes it. The minimax algorithm is used to allow the agent to search X moves ahead and figure out which produces the best possible outcome for itself, and the worst possible outcome for the other player. Each move/new gamestate is represented within a Node, and each Node hold a vector of other Nodes.
 *
 */
/*  */
#include <vector>

#include "chessboard.h"

/// The Node structure is what makes up the tree of game states/moves traversed within Agent
class Node {
   public:
    Node(Chessboard state, std::pair<int, int> move) : board_state(state), move(move), score(0) {}
    /// clears out the tree created for the previous move's game state recursively
    void reset_tree_recursive();

    Chessboard board_state;
    std::pair<int, int> move;
    int score;
    std::vector<Node *> children;

   private:
    Node(Node &&other) = delete;
    Node &operator=(Node &&other) = delete;
};

/// Class used to programmatically produce a Chess move
class Agent {
   public:
    Agent(Chessboard initial_board);
    Node *root;
    std::pair<int, int> find_best_move(int depth);

    /// Calls the recursive function inside Node
    void reset_tree(Chessboard state);

   private:
    void initialize_piece_structure_bonus();
    std::vector<std::pair<int, int>> generate_possible_moves(Node *node, bool b_team);

    /// Constructs the tree where each layer is one move ahead of the current state
    void generate_tree(Node *node, int depth, bool b_team);
    /// Recursively traverse tree of game states with a possible move applied, calling evaluate() on each move
    int minimax(Node *node, int depth, int alpha, int beta, bool maximizingPlayer);
    int min(int a, int b);
    int max(int a, int b);

    /// Calculates a given game state's 'score' based on all piece values, the mobility of said pieces, and the structure of their formation
    int evaluate(Chessboard state);

    /// Constant time lookup for what structure to use
    std::vector<int> get_piece_structure(Piece piece);
    int get_piece_value(Type type);

    /// vector of piece values ordered to allow constant time lookups
    std::vector<int> piece_values;

    /**
     * @brief vector of piece structures ordered to allow constant time lookups
     *
     * piece structures are used for scoring a game state based on the position of pieces given a game state
     */
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

    /**
     * @brief end game king structures
     *
     * End game king structures are used to help promote the agent in making better decisions with its king or against the enemy king late game. More points for keeping king centered, less for the king being near the edges making checks/mates easier
     */
    std::vector<int> end_king_structure_white;
    std::vector<int> end_king_structure_black;

    Agent(const Agent &other) = delete;
    Agent &operator=(const Agent &other) = delete;
    Agent(Agent &&other) = delete;
    Agent &operator=(Agent &&other) = delete;
};
