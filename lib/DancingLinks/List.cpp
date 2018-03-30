#include "DancingLinks.hpp"

namespace DancingLinks {
List::List(int rowCount, int columnCount)
    : Columns(std::vector<BaseNode>(columnCount)),
      Rows(std::vector<BaseNode>(rowCount)) {

  Columns.front().Right = &Columns.at(1);
  Columns.back().Left = &Columns.at(Columns.size() - 2);
  for (int i = 1; i < Columns.size() - 1; ++i) {
    Columns.at(i).Left = &Columns.at(i - 1);
    Columns.at(i).Right = &Columns.at(i + 1);
  }

  Rows.front().Down = &Rows.at(1);
  Rows.back().Up = &Rows.at(Rows.size() - 2);
  for (int i = 1; i < Rows.size() - 1; ++i) {
    Rows.at(i).Up = &Rows.at(i - 1);
    Rows.at(i).Down = &Rows.at(i + 1);
  }

  RootColumn = &Columns.at(0);
}

void List::insertNode(int row, int column) {
  BaseNode& rowNode = Rows.at(row);
  BaseNode& columnNode = Columns.at(column);
  Nodes.push_back(std::make_unique<ListNode>());
  ListNode* newNode = Nodes.back().get();
  newNode->Up = columnNode.Last;
  newNode->Left = rowNode.Last;
  newNode->Column = &columnNode;
  newNode->Row = &rowNode;
  columnNode.Last = newNode;
  rowNode.Last = newNode;

  newNode->link();
}

void List::unlinkRow(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* left = cell->Left; left != nullptr; left = left->Left) {
    left->unlink();
  }
  for (ListNode* right = cell->Right; right != nullptr; right = right->Right) {
    right->unlink();
  }
}

void List::unlinkColumn(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* up = cell->Up; up != nullptr; up = up->Up) {
    up->unlink();
  }
  for (ListNode* down = cell->Down; down != nullptr; down = down->Down) {
    down->unlink();
  }
  if (cell->Column->Left == nullptr) {
    assert(cell->Column == RootColumn);
    RootColumn = static_cast<BaseNode*>(cell->Column->Right);
  }
}

void List::linkRow(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* left = cell->Left; left != nullptr; left = left->Left) {
    left->link();
  }
  for (ListNode* right = cell->Right; right != nullptr; right = right->Right) {
    right->link();
  }
}

void List::linkColumn(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* up = cell->Up; up != nullptr; up = up->Up) {
    up->link();
  }
  for (ListNode* down = cell->Down; down != nullptr; down = down->Down) {
    down->link();
  }
  if (cell->Column->Left == nullptr) {
    RootColumn = static_cast<BaseNode*>(cell->Column);
  }
}
int List::getColumnCount() const {
  int result = 0;
  for (auto& x : Columns) {
    if (x.getCount() > 0) {
      ++result;
    }
  }
  return result;
}

std::pair<int, int> List::getCoord(ListNode* node) const {
  int rowIndex = node->Row - &Rows[0];
  assert(rowIndex < Rows.size());
  int columnIndex = node->Column - &Columns[0];
  assert(columnIndex < Columns.size());
  return std::make_pair(rowIndex, columnIndex);
}
} // namespace DancingLinks
