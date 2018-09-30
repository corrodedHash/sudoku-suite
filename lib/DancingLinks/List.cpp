#include "DancingLinks/List.hpp"

#include "DancingLinks/LineIterator.hpp"
#include "DancingLinks/Node.hpp"

#include <algorithm>
#include <deque>
#include <iterator>
#include <utility>

namespace DancingLinks {
List::List(std::deque<Node>&& nodes, std::deque<ColumnNode>&& columnNodes,
           Node* header) :
    Nodes(std::forward<std::deque<Node>>(nodes)),
    ColumnNodes(std::forward<std::deque<ColumnNode>>(columnNodes)),
    Header(header) {}

void
List::coverColumn(ColumnNode* columnNode) {
  columnNode->Left->Right = columnNode->Right;
  columnNode->Right->Left = columnNode->Left;
  for (Node& rowNode : ColumnExcludingView(columnNode)) {
    for (Node& cellNode : RowExcludingView(&rowNode)) {
      cellNode.Up->Down = cellNode.Down;
      cellNode.Down->Up = cellNode.Up;
    }
  }
}

void
List::uncoverColumn(ColumnNode* columnNode) {
  for (Node& rowNode : ColumnExcludingView(columnNode)) {
    for (Node& cellNode : RowExcludingView(&rowNode)) {
      cellNode.Up->Down = &cellNode;
      cellNode.Down->Up = &cellNode;
    }
  }
  columnNode->Right->Left = columnNode;
  columnNode->Left->Right = columnNode;
}

bool
List::containsEmptyColumn() {
  RowExcludingView rowView(Header);
  return std::any_of(std::begin(rowView), std::end(rowView),
                     [](const Node& node) { return node.Down == &node; });
}

bool
List::isEmpty() {
  return Header->Right == Header;
}
} // namespace DancingLinks
