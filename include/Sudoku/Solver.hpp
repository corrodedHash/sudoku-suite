#pragma once
#include "DancingLinks/Solver.hpp"
#include "Sudoku/Field.hpp"

#include <optional>

namespace Sudoku {
/// @brief Sudoku solver class
class Solver {
  DancingLinks::Solver PuzzleSolver;
  int Blocksize;

public:
  Solver(const Field& puzzle);

  /// @brief Returns a solution to the puzzle that has not yet been returned
  ///
  /// @return Either a completed sudoku field, or nullopt
  std::optional<Field> nextSolution();
};
} // namespace Sudoku
