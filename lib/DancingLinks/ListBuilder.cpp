#include "DancingLinks/ListBuilder.hpp"

#include "DancingLinks/List.hpp"
#include "DancingLinks/Node.hpp"

#include <algorithm>
#include <cassert>
#include <deque>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

namespace DancingLinks {
ListBuilder::ListBuilder() { Header = &(Nodes.emplace_back()); }

ListBuilder::ListBuilder(int rowCount, int columnCount) {
  Header = &(Nodes.emplace_back());

  ColumnNodes.resize(columnCount);

  Row.resize(rowCount, nullptr);
  Column.reserve(columnCount);

  std::transform(std::begin(ColumnNodes), std::end(ColumnNodes),
                 std::back_inserter(Column), [](auto& node) { return &node; });

  int current_id = 0;
  for (auto& node : ColumnNodes) {
    node.linkHorizontally(Header->Left, Header);
    node.Id = current_id;
    ++current_id;
  }
}

void
ListBuilder::insertNode(int row, int column) {
  assert(Row.size() > row);
  assert(Column.size() > column);

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
