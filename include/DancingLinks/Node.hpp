#pragma once
namespace DancingLinks {
struct ColumnNode;
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

} // namespace DancingLinks
