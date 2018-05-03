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
      NewColumnNode.linkHorizontally(Header->Left, Header);
    }
  }

  if (Row.size() <= row) {
    Row.resize(row + 1, nullptr);
  }

  Node& NewNode = Nodes.emplace_back();

  if (Row[row] == nullptr) {
    Row[row] = &NewNode;
  } else {
    NewNode.linkHorizontally(Row[row]->Left, Row[row]);
  }

  NewNode.linkVertically(Column[column]->Up, Column[column]);

  NewNode.Column = Column[column];
}

void
ListBuilder::print(std::ostream& stream) {
  constexpr char hitChar = 'X';
  constexpr char missChar = ' ';
  for (Node* row : Row) {
    for (int i = 0; i < Column.size(); ++i) {
      if ((row != nullptr) && (i == row->Column->Id)) {
        stream << hitChar;
        row = row->Right;
      } else {
        stream << missChar;
      }
    }
    stream << '\n';
  }
}

List
ListBuilder::finalize() {
  return List(std::move(Nodes), std::move(ColumnNodes), Header);
}
} // namespace DancingLinks
