#pragma once
#include <array>
#include <cassert>
#include <memory>
#include <stack>
#include <vector>
#include <iostream>
#include <map>

namespace DancingLinks {
struct ListNode;

struct BaseNode;
struct ListNode {
  ListNode *Left, *Right, *Up, *Down;
  BaseNode* Row;
  BaseNode* Column;

  void registerBase();
  void unregisterBase();
  void registerNeighbors();
  void unregisterNeighbors();

  virtual void unlink();
  virtual void link();
};

struct BaseNode : public ListNode {
private:
  int Count;

public:
  ListNode* Last = this;
  int getCount() const;

  void registerNode();
  void unregisterNode();
  void unlink();
  void link();
};

struct List {
  std::vector<BaseNode> Columns;
  std::vector<BaseNode> Rows;
  std::vector<std::unique_ptr<ListNode>> Nodes;
  BaseNode* RootColumn;

  List(int rowCount, int columnCount);

  bool isEmpty() { return RootColumn == nullptr; }

  void insertNode(int row, int column);
  int getColumnCount() const;
  std::pair<int, int> getCoord(ListNode* node) const;

  void unlinkRow(ListNode* cell);
  void unlinkColumn(ListNode* cell);
  void linkRow(ListNode* cell);
  void linkColumn(ListNode* cell);
};

class Solver {
  List List;
  std::vector<ListNode*> Removed;
  std::stack<int> TestedId;

  void unlinkNode(DancingLinks::ListNode* toUnlink);
  void linkNode(DancingLinks::ListNode* toLink);
  ListNode* get(int id);
  bool checkListEmptyColumn();

public:
  Solver(struct List list) : List(std::move(list)) { TestedId.push(0); }
  void backtrack();
  void deepen(ListNode* node);
  std::optional<std::vector<int>> nextModel();
};
} // namespace DancingLinks
