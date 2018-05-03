#include "DancingLinks.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

namespace DancingLinks {
Solver::Solver(List exactCoverPuzzle) :
    ExactCoverPuzzle(std::move(exactCoverPuzzle)) {}

void
Solver::deepen() {
  while (true) {
    // Stop deepening if solution found
    if (ExactCoverPuzzle.Header->Right == ExactCoverPuzzle.Header) {
      return;
    }

    // Stop deepening if guessed wrong
    for (Node* curNode = ExactCoverPuzzle.Header->Right;
         curNode != ExactCoverPuzzle.Header; curNode = curNode->Right) {
      if (curNode->Down == curNode) {
        return;
      }
    }

    AssumedNodes.push_back(ExactCoverPuzzle.Header->Right->Down);
    ExactCoverPuzzle.coverColumn(AssumedNodes.back()->Column);

    for (Node* curNode = AssumedNodes.back()->Right;
         curNode != AssumedNodes.back(); curNode = curNode->Right) {
      ExactCoverPuzzle.coverColumn(curNode->Column);
    }
  }
}

void
Solver::backtrack() {
  while (!AssumedNodes.empty()) {
    for (Node* curNode = AssumedNodes.back()->Left;
         curNode != AssumedNodes.back(); curNode = curNode->Left) {
      ExactCoverPuzzle.uncoverColumn(curNode->Column);
    }

    if (AssumedNodes.back()->Down == AssumedNodes.back()->Column) {
      ExactCoverPuzzle.uncoverColumn(AssumedNodes.back()->Column);
      AssumedNodes.pop_back();
    } else {

      AssumedNodes.back() = AssumedNodes.back()->Down;

      for (Node* curNode = AssumedNodes.back()->Right;
           curNode != AssumedNodes.back(); curNode = curNode->Right) {
        ExactCoverPuzzle.coverColumn(curNode->Column);
      }

      return;
    }
  }
  Finished = true;
}

std::optional<std::vector<Node*>>
Solver::nextModel() {
  if (!Finished &&
      (ExactCoverPuzzle.Header->Right == ExactCoverPuzzle.Header)) {
    backtrack();
  }
  while (!Finished) {
    deepen();

    if (ExactCoverPuzzle.Header->Right == ExactCoverPuzzle.Header) {
      return AssumedNodes;
    }

    backtrack();
  }
  return std::nullopt;
}
} // namespace DancingLinks
