#pragma once

#include <array>
#include <deque>
#include <map>
#include <memory>
#include <vector>

namespace DancingLinks {
class ColumnNode;
/// @brief Node in a DancingLinks list
struct Node {
  Node *Left = this, *Right = this, *Up = this, *Down = this;
  ColumnNode* Column;
  int RowIndex;
};

/// @brief First node in a column of a DancingLinks list
struct ColumnNode : public Node {
  int Count;
  int Id;
};

/// @brief Circular DancingLinks list
class List {
  std::deque<Node> Nodes;
  std::deque<ColumnNode> ColumnNodes;

public:
  Node* const Header;

  /// @brief Constructor that is used by ListBuilder
  ///
  /// @param nodes Collection of internal list nodes
  /// @param columnNodes Collection of the column nodes
  /// @param header Additional node which is left of the header nodes
  List(std::deque<Node>&& nodes, std::deque<ColumnNode>&& columnNodes,
       Node* header);
  List(const List& other) = delete;
  List(List&& other) = default;
  void coverColumn(ColumnNode* columnNode);
  void uncoverColumn(ColumnNode* columnNode);
};

/// @brief Builder for List
class ListBuilder {
  std::vector<ColumnNode*> Column;
  std::vector<Node*> Row;
  std::deque<Node> Nodes;
  std::deque<ColumnNode> ColumnNodes;
  Node* Header;

public:
  ListBuilder();

  /// @brief Add a node into the list. Must build from top left to bottom right.
  void insertNode(int row, int column);

  /// @brief Create the list. Invalidates ListBuilder
  ///
  /// @return The created list
  List finalize();

  void print(std::ostream& stream);
};

/// @brief Solver for ExactCover problem in a DancingLinks List
class Solver {
  List ExactCoverPuzzle;
  std::vector<Node*> AssumedNodes;
  bool Finished = false;
  void backtrack();
  bool deepen();

public:
  Solver(List exactCoverPuzzle);

  /// @brief Returns a solution to the puzzle that has not yet been returned
  ///
  /// @return Either a list of nodes representing each row, or nullopt
  std::optional<std::vector<Node*>> nextModel();
};
} // namespace DancingLinks
