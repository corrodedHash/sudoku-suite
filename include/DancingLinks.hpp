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
class ListNode {
protected:
  bool Unlinked = true;

  void registerBase();
  void unregisterBase();
  void registerNeighbors();
  void unregisterNeighbors();

public:
  ListNode() = default;
  ListNode(const ListNode& other) = delete;
  ListNode *Left, *Right, *Up, *Down;
  BaseNode* Row;
  BaseNode* Column;

  virtual void unlink();
  virtual void link();
};

class BaseNode : public ListNode {
private:
  int Count;

public:
  BaseNode() = default;
  ListNode* Last = this;
  int getCount() const;

  void registerNode();
  void unregisterNode();
  void unlink();
  void link();
};

class List {
private:
  std::vector<BaseNode> Columns;
  std::vector<BaseNode> Rows;
  std::vector<std::unique_ptr<ListNode>> Nodes;
  ListNode RootNode;

public:
  List(int rowCount, int columnCount);
  List(const List& other) = delete;

  bool
  isEmpty() {
    return getFirstColumn() == nullptr;
  }

  BaseNode*
  getFirstColumn() {
    return static_cast<BaseNode*>(RootNode.Right);
  }

  BaseNode*
  getFirstRow() {
    return static_cast<BaseNode*>(RootNode.Down);
  }

  void insertNode(int row, int column);
  int getColumnCount() const;
  std::pair<int, int> getCoord(ListNode* node) const;

  void unlinkRow(ListNode* cell);
  void unlinkColumn(ListNode* cell);
  void linkRow(ListNode* cell);
  void linkColumn(ListNode* cell);

  void print();
};

class Solver {
  std::unique_ptr<List> List;
  std::vector<ListNode*> Removed;
  ListNode* CurrentGuessedRow;

  void assumeRow(ListNode* row);
  void resetRow(ListNode* row);
  ListNode* get(int id);
  bool checkListEmptyColumn();

public:
  Solver(std::unique_ptr<struct List>&& list) : List(std::move(list)) {
    CurrentGuessedRow = List->getFirstRow();
  }
  bool backtrack();
  void deepen(ListNode* node);
  std::optional<std::vector<int>> nextModel();
};
} // namespace DancingLinks
