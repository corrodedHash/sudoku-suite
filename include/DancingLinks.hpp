#pragma once

#include <array>
#include <deque>
#include <iterator>
#include <map>
#include <memory>
#include <vector>

namespace DancingLinks {
class ColumnNode;
/// @brief Node in a DancingLinks list
struct Node {
  Node *Left = this, *Right = this, *Up = this, *Down = this;
  ColumnNode* Column;

  void linkHorizontally(Node* left, Node* right);
  void linkVertically(Node* up, Node* down);
};

/// @brief First node in a column of a DancingLinks list
struct ColumnNode : public Node {
  int Count;
  int Id;
};

class RowExcludingRightIterator {
private:
  Node* StartNode;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = Node;
  using pointer = Node*;
  using reference = Node&;
  using difference_type = long;

  RowExcludingRightIterator(Node* node) : StartNode(node->Right) {}

  RowExcludingRightIterator& operator++() {
    StartNode = StartNode->Right;
    return *this;
  }
  RowExcludingRightIterator operator++(int) {
    RowExcludingRightIterator buffer = *this;
    StartNode = StartNode->Right;
    return buffer;
  }

  pointer operator->() const { return StartNode; }
  reference operator*() const { return *StartNode; }

  bool operator==(const RowExcludingRightIterator& other) const {
    return other.StartNode == StartNode;
  }
  bool operator!=(const RowExcludingRightIterator& other) const {
    return !(*this == other);
  }
};

} // namespace DancingLinks

template <>
struct std::iterator_traits<DancingLinks::RowExcludingRightIterator> {
  using iterator_category =
      DancingLinks::RowExcludingRightIterator::iterator_category;
  using value_type = DancingLinks::RowExcludingRightIterator::value_type;
  using pointer = DancingLinks::RowExcludingRightIterator::pointer;
  using reference = DancingLinks::RowExcludingRightIterator::reference;
  using difference_type =
      DancingLinks::RowExcludingRightIterator::difference_type;
};

namespace DancingLinks {
class RowExcludingRightView {
  Node* StartNode;

public:
  RowExcludingRightView(Node* node) : StartNode(node) {}
  RowExcludingRightIterator begin() {
    return RowExcludingRightIterator(StartNode);
  }
  RowExcludingRightIterator end() {
    return RowExcludingRightIterator(StartNode->Left);
  }
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

  bool containsEmptyColumn();
  bool isEmpty();
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
  ListBuilder(int rowCount, int columnCount);

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

  void deepen();
  void backtrack();

public:
  Solver(List exactCoverPuzzle);

  /// @brief Returns a solution to the puzzle that has not yet been returned
  ///
  /// @return Either a list of nodes representing each row, or nullopt
  std::optional<std::vector<Node*>> nextModel();
};
} // namespace DancingLinks
