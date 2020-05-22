#pragma once
#include "DancingLinks/Node.hpp"

#include <deque>

namespace DancingLinks {

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

  static void coverColumn(ColumnNode* columnNode);
  static void uncoverColumn(ColumnNode* columnNode);

  [[nodiscard]] auto containsEmptyColumn() const -> bool;
  [[nodiscard]] auto isEmpty() const -> bool;
};
} // namespace DancingLinks
