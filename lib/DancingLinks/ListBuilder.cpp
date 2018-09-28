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
  assert(row >= 0);
  assert(column >= 0);
  assert(Row.size() > static_cast<std::size_t>(row));
  assert(Column.size() > static_cast<std::size_t>(column));

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
    for (std::size_t i = 0; i < Column.size(); ++i) {
      assert(row->Column->Id >= 0);
      if ((row != nullptr) && (i == static_cast<std::size_t>(row->Column->Id))) {
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
