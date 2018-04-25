#include "DancingLinks.hpp"

#include <cassert>
#include <iomanip>
#include <iostream>

// Can be improved by not unlinking the main column
namespace DancingLinks {
List::List(std::vector<std::unique_ptr<Node>> nodes, Node* header) :
    Nodes(std::move(nodes)), Header(header) {}

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
} // namespace DancingLinks
