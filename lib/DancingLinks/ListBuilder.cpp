#include "DancingLinks.hpp"

#include <cassert>
#include <iostream>

namespace DancingLinks {
ListBuilder::ListBuilder() {
  Nodes.emplace_back();
  Header = &(Nodes.back());
}

void
ListBuilder::insertNode(int row, int column) {
  if (Column.size() <= column) {
    Column.reserve(column + 1);
    while (Column.size() <= column) {
      ColumnNode& NewColumnNode = ColumnNodes.emplace_back();

      Column.push_back(&NewColumnNode);

      NewColumnNode.Id = ColumnNodes.size() - 1;
      NewColumnNode.Right = Header;
      NewColumnNode.Left = Header->Left;
      NewColumnNode.Right->Left = &NewColumnNode;
      NewColumnNode.Left->Right = &NewColumnNode;
    }
  }

  if (Row.size() <= row) {
    Row.resize(row + 1, nullptr);
  }

  Node& NewNode = Nodes.emplace_back();

  if (Row[row] == nullptr) {
    Row[row] = &NewNode;
  } else {
    NewNode.Right = Row[row];
    NewNode.Left = Row[row]->Left;
    NewNode.Right->Left = &NewNode;
    NewNode.Left->Right = &NewNode;
  }

  NewNode.Down = Column[column];
  NewNode.Up = Column[column]->Up;
  NewNode.Down->Up = &NewNode;
  NewNode.Up->Down = &NewNode;

  NewNode.Column = Column[column];
  NewNode.RowIndex = row;
}

void
ListBuilder::print() {
  for (Node* row : Row) {
    for (int i = 0; i < Column.size(); ++i) {
      if (i == row->Column->Id) {
        std::cout << "X";
        row = row->Right;
      } else {
        std::cout << " ";
        //assert(row->Column->Id > i);
      }
    }
    std::cout << '\n';
  }
}

List
ListBuilder::finalize() {
  return List(std::move(Nodes), std::move(ColumnNodes), Header);
}
} // namespace DancingLinks
