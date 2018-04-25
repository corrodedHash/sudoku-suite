#include "DancingLinks.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

namespace DancingLinks {
Solver::Solver(List exactCoverPuzzle) :
    ExactCoverPuzzle(std::move(exactCoverPuzzle)) {}

bool
Solver::deepen() {
  if (ExactCoverPuzzle.Header->Right == ExactCoverPuzzle.Header) {
    return false;
  }

  for (Node* curNode = ExactCoverPuzzle.Header->Right;
       curNode != ExactCoverPuzzle.Header; curNode = curNode->Right) {
    if (curNode->Down == curNode) {
      return false;
    }
  }

  AssumedNodes.push_back(ExactCoverPuzzle.Header->Right->Down);
  ExactCoverPuzzle.coverColumn(AssumedNodes.back()->Column);

  for (Node* curNode = AssumedNodes.back()->Right;
       curNode != AssumedNodes.back(); curNode = curNode->Right) {
    ExactCoverPuzzle.coverColumn(curNode->Column);
  }

  return true;
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

std::optional<std::vector<int>>
Solver::nextModel() {
  while (!Finished) {
    while (deepen()) {
      // Deepen as long as possible
    }

    if (ExactCoverPuzzle.Header->Right == ExactCoverPuzzle.Header) {
      std::vector<int> result(AssumedNodes.size());
      std::transform(AssumedNodes.begin(), AssumedNodes.end(), result.begin(),
                     [](Node* node) { return node->RowIndex; });
      backtrack();
      return result;
    }
    backtrack();
  }
  return std::nullopt;
}
} // namespace DancingLinks
