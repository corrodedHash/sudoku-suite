#pragma once
#include "DancingLinks/List.hpp"

#include <optional>
#include <vector>

namespace DancingLinks {

/// @brief Solver for ExactCover problem in a DancingLinks List
struct Node;

class Solver {
  List ExactCoverPuzzle;
  std::vector<Node*> AssumedNodes;
  bool Finished = false;

  void deepen();
  void backtrack();

public:
  Solver(List exactCoverPuzzle);

  /// @brief Returns a solution to the puzzle that has not yet been returned
  ///
  /// @return Either a list of nodes representing each row, or nullopt
  auto nextModel() -> std::optional<std::vector<Node*>>;
};
} // namespace DancingLinks
