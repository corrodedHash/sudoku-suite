#pragma once

#include <array>
#include <map>
#include <memory>
#include <stack>
#include <vector>

namespace DancingLinks {
class ColumnNode;
class Node {
public:
  Node *Left = this, *Right = this, *Up = this, *Down = this;
  ColumnNode* Column;
  int RowIndex;
};

class ColumnNode : public Node {
  int Count;
};

class List {
  std::vector<std::unique_ptr<Node>> Nodes;

public:
  Node* Header;
  List(std::vector<std::unique_ptr<Node>> nodes, Node* header);
  List(const List& other) = delete;
  List(List&& other) = default;
  void coverColumn(ColumnNode* columnNode);
  void uncoverColumn(ColumnNode* columnNode);
};

class ListBuilder {
  std::vector<ColumnNode*> Column;
  std::vector<Node*> Row;
  std::vector<std::unique_ptr<Node>> Nodes;
  Node* Header;

public:
  ListBuilder();

  void insertNode(int row, int column);
  List finalize();
};

class Solver {
  List ExactCoverPuzzle;
  std::vector<Node*> AssumedNodes;
  bool Finished = false;
  void backtrack();
  bool deepen();

public:
  Solver(List exactCoverPuzzle);
  std::optional<std::vector<int>> nextModel();
};
} // namespace DancingLinks
