#pragma once
#include <array>
#include <memory>
#include <stack>
#include <vector>
#include <map>

namespace DancingLinks {
class BaseNode;

/// @brief Node in DancingLinks::List
class ListNode {
protected:
  bool Unlinked = true;

  /// @brief Notify base nodes that this node was added to the list
  void registerBase();
  /// @brief Notify base nodes that this node was removed from the list
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

/// @brief Empty node at the beginning of each row/column
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
  ListNode* CurrentGuessedRow;
  /// @brief ListNodes in the removed rows
  std::vector<ListNode*> RemovedRows;

  void assumeRow(ListNode* row);
  void resetRow(ListNode* row);
  bool containsEmptyColumn();

  /// @brief Remove newest assumption and reset the list
  ///
  /// @return True if the searchtree is now empty
  bool backtrack();

  /// @brief Add assumption and reduce list
  ///
  /// @param node The node in the assumed row
  void deepen(ListNode* node);

public:
  Solver(std::unique_ptr<struct List>&& list) : List(std::move(list)) {
    CurrentGuessedRow = List->getFirstRow();
  }
  /// @brief Calculate a solution for the given exact cover problem, which is
  /// different from the previous solutions
  ///
  /// @return A vector of rows which are in the solution, or false if no
  /// solution could be found
  std::optional<std::vector<int>> nextModel();
};
} // namespace DancingLinks
