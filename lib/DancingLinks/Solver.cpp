#include "DancingLinks/Solver.hpp"

#include "DancingLinks/List.hpp"
#include "DancingLinks/Node.hpp"

#include <optional>
#include <utility>
#include <vector>

namespace DancingLinks {
Solver::Solver(List exactCoverPuzzle) :
    ExactCoverPuzzle(std::move(exactCoverPuzzle)) {}

void
Solver::deepen() {
  while (!ExactCoverPuzzle.isEmpty() &&
         !ExactCoverPuzzle.containsEmptyColumn()) {
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

auto
Solver::nextModel() -> std::optional<std::vector<Node*>> {
  while (!Finished) {
    deepen();

    if (ExactCoverPuzzle.isEmpty()) {
      auto result = AssumedNodes;
      backtrack();
      return result;
    }

    backtrack();
  }
  return std::nullopt;
}
} // namespace DancingLinks
