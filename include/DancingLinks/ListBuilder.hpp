#pragma once
#include "DancingLinks/List.hpp"
#include "DancingLinks/Node.hpp"

#include <deque>
#include <ostream>
#include <vector>

namespace DancingLinks {
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
  auto finalize() -> List;

  void print(std::ostream& stream);
};
} // namespace DancingLinks
