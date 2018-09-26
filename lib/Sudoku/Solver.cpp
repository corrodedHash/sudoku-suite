#include "Sudoku/Solver.hpp"

#include "Sudoku/DLHelper.hpp"

#include <cassert>

namespace Sudoku {
Solver::Solver(const Field& puzzle) :
    PuzzleSolver(DancingLinks::Solver(DLHelper::toDancingLinksList(puzzle))),
    Blocksize(puzzle.getBlocksize()) {
  assert(puzzle.correct());
}

std::optional<Field>
Solver::nextSolution() {
  auto exactCoverResult = PuzzleSolver.nextModel();
  if (!exactCoverResult) {
    return std::nullopt;
  }
  return DLHelper::fromDancingLinksList(*exactCoverResult, Blocksize);
}
} // namespace Sudoku
