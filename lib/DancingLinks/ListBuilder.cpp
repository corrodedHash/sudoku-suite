#include "DancingLinks.hpp"

namespace DancingLinks {
ListBuilder::ListBuilder() {
  Nodes.push_back(std::make_unique<Node>());
  Header = Nodes.back().get();
}

void
ListBuilder::insertNode(int row, int column) {
  if (Column.size() <= column) {
    Column.reserve(column + 1);
    while (Column.size() <= column) {
      Nodes.push_back(std::make_unique<ColumnNode>());
      Column.push_back(static_cast<ColumnNode*>(Nodes.back().get()));

      Nodes.back()->Right = Header;
      Nodes.back()->Left = Header->Left;
      Nodes.back()->Right->Left = Nodes.back().get();
      Nodes.back()->Left->Right = Nodes.back().get();
    }
  }

  if (Row.size() <= row) {
    Row.resize(row + 1, nullptr);
  }

  Nodes.push_back(std::make_unique<Node>());

  if (Row[row] == nullptr) {
    Row[row] = Nodes.back().get();
  } else {
    Nodes.back()->Right = Row[row];
    Nodes.back()->Left = Row[row]->Left;
    Nodes.back()->Right->Left = Nodes.back().get();
    Nodes.back()->Left->Right = Nodes.back().get();
  }

  Nodes.back()->Down = Column[column];
  Nodes.back()->Up = Column[column]->Up;
  Nodes.back()->Down->Up = Nodes.back().get();
  Nodes.back()->Up->Down = Nodes.back().get();

  Nodes.back()->Column = Column[column];
  Nodes.back()->RowIndex = row;
}

List
ListBuilder::finalize() {
  return List(std::move(Nodes), Header);
}
} // namespace DancingLinks
