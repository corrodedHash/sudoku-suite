#include "DancingLinks.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>
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
  for (Node* mainColumnEntry = columnNode->Down; mainColumnEntry != columnNode;
       mainColumnEntry = mainColumnEntry->Down) {
    for (Node* currentRowEntry = mainColumnEntry->Right;
         currentRowEntry != mainColumnEntry;
         currentRowEntry = currentRowEntry->Right) {
      currentRowEntry->Up->Down = currentRowEntry->Down;
      currentRowEntry->Down->Up = currentRowEntry->Up;
    }
  }
}

void
List::uncoverColumn(ColumnNode* columnNode) {
  for (Node* mainColumnEntry = columnNode->Up; mainColumnEntry != columnNode;
       mainColumnEntry = mainColumnEntry->Up) {
    for (Node* currentRowEntry = mainColumnEntry->Left;
         currentRowEntry != mainColumnEntry;
         currentRowEntry = currentRowEntry->Left) {
      currentRowEntry->Down->Up = currentRowEntry;
      currentRowEntry->Up->Down = currentRowEntry;
    }
  }
  columnNode->Right->Left = columnNode;
  columnNode->Left->Right = columnNode;
}

bool
List::containsEmptyColumn() {
  for (Node* curNode = Header->Right; curNode != Header;
       curNode = curNode->Right) {
    if (curNode->Down == curNode) {
      return true;
    }
  }
  return false;
}

bool
List::isEmpty() {
  return Header->Right == Header;
}
} // namespace DancingLinks
