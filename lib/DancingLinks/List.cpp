#include "DancingLinks.hpp"
#include <iomanip>

namespace DancingLinks {
List::List(int rowCount, int columnCount)
    : Columns(std::vector<BaseNode>(columnCount)),
      Rows(std::vector<BaseNode>(rowCount)) {
  assert(rowCount > 0);
  assert(columnCount > 0);
  Columns.at(Columns.size() - 1).Column = &Columns.at(Columns.size() - 1);
  Rows.at(Rows.size() - 1).Row = &Rows.at(Rows.size() - 1);

  for (int i = 0; i < Columns.size() - 1; ++i) {
    Columns.at(i).Column = &Columns.at(i);
    Columns.at(i).Right = &Columns.at(i + 1);
    Columns.at(i + 1).Left = &Columns.at(i);
  }

  for (int i = 0; i < Rows.size() - 1; ++i) {
    Rows.at(i).Row = &Rows.at(i);
    Rows.at(i).Down = &Rows.at(i + 1);
    Rows.at(i + 1).Up = &Rows.at(i);
  }

  RootNode.Right = &Columns.at(0);
  Columns.at(0).Left = &RootNode;

  RootNode.Down = &Rows.at(0);
  Rows.at(0).Up = &RootNode;
}

BaseNode* List::getFirstColumn() {
  return static_cast<BaseNode*>(RootNode.Right);
}

BaseNode* List::getFirstRow() { return static_cast<BaseNode*>(RootNode.Down); }

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
  for (ListNode* right = cell->Row; right != nullptr; right = right->Right) {
    right->unlink();
  }
}

void List::unlinkColumn(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* down = cell->Column; down != nullptr; down = down->Down) {
    down->unlink();
  }
}

void List::linkRow(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* right = cell->Row; right != nullptr; right = right->Right) {
    right->link();
  }
}

void List::linkColumn(ListNode* cell) {
  assert(cell != nullptr);
  for (ListNode* down = cell->Column; down != nullptr; down = down->Down) {
    down->link();
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
  std::pair<int, int> result;
  if (node->Row == nullptr) {
    result.first = -1;
  } else {
    result.first = node->Row - &Rows[0];
  }
  if (node->Column == nullptr) {
    result.second = -1;

  } else {
    result.second = node->Column - &Columns[0];
  }
  return result;
}

void List::print() {
  int cellWidth = 3;
  std::string cellSeperator = " | ";
  std::cout << std::setw(cellWidth) << " ";
  std::cout << cellSeperator;
  for (ListNode* curColumn = getFirstColumn(); curColumn != nullptr;
       curColumn = curColumn->Right) {
    std::cout << std::setw(cellWidth)
              << static_cast<BaseNode*>(curColumn) - &Columns[0];
    std::cout << cellSeperator;
  }
  std::cout << '\n';
  for (ListNode* curRow = getFirstRow(); curRow != nullptr;
       curRow = curRow->Down) {
    ListNode* curCell = curRow->Right;
    std::cout << std::setw(cellWidth)
              << static_cast<BaseNode*>(curRow) - &Rows[0] << cellSeperator;
    for (ListNode* curColumn = getFirstColumn(); curColumn != nullptr;
         curColumn = curColumn->Right) {
      if (curCell == nullptr || curCell->Column != curColumn) {
        std::cout << std::setw(cellWidth) << "-";
      } else {
        curCell = curCell->Right;
        std::cout << std::setw(cellWidth) << "X";
      }
      std::cout << cellSeperator;
    }
    std::cout << '\n';
  }
}
} // namespace DancingLinks
