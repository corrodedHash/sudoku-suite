#pragma once
#include "DancingLinks/Node.hpp"

#include <deque>

/// @brief Circular DancingLinks list
namespace DancingLinks {
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
} // namespace DancingLinks
