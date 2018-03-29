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

  bool isEmpty()
  {
    return RootColumn == nullptr;
  }

  void insertNode(int row, int column);
  int getColumnCount() const;
  std::pair<int, int> getCoord(ListNode* node) const;

  void unlinkRow(ListNode* cell);
  void unlinkColumn(ListNode* cell);
  void linkRow(ListNode* cell);
  void linkColumn(ListNode* cell);
};

struct Solver {
  List List;
  std::vector<ListNode*> Removed;
  std::stack<int> TestedId;
  Solver(struct List list)
      : List(std::move(list))
  {
    TestedId.push(0);
  }

  void unlinkNode(DancingLinks::ListNode* toUnlink);
  void linkNode(DancingLinks::ListNode* toLink);
  ListNode* get(int id);
  void backtrack();
  void deepen(ListNode* node);
  bool nextModel();
  bool checkListEmptyColumn();
};
}
int getColId(int row, int col, int number);

template <int T>
std::array<std::array<bool, T * T * T * T * 4>, T * T * T * T * T * T> createExactCover();

template <int T>
DancingLinks::List toDancingLinksList(std::array<std::array<bool, T * T * T * T * 4>, T * T * T * T * T * T> matrix);

template <int T> void drawSudoku(const DancingLinks::Solver& s);

#include "DancingLinks.tpp"
