#pragma once

#include <array>
#include <map>
#include <memory>
#include <vector>
#include <deque>

namespace DancingLinks {
class ColumnNode;
struct Node {
  Node *Left = this, *Right = this, *Up = this, *Down = this;
  ColumnNode* Column;
  int RowIndex;
};

struct ColumnNode : public Node {
  int Count;
  int Id;
};

class List {
  std::deque<Node> Nodes;
  std::deque<ColumnNode> ColumnNodes;

public:
  Node* Header;
  List(std::deque<Node>&& nodes, std::deque<ColumnNode>&& columnNodes, Node* header);
  void coverColumn(ColumnNode* columnNode);
  void uncoverColumn(ColumnNode* columnNode);
};

class ListBuilder {
  std::vector<ColumnNode*> Column;
  std::vector<Node*> Row;
  std::deque<Node> Nodes;
  std::deque<ColumnNode> ColumnNodes;
  Node* Header;

public:
  ListBuilder();

  void insertNode(int row, int column);
  void print();
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
  std::optional<std::vector<Node*>> nextModel();
};
} // namespace DancingLinks
