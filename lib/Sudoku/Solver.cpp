#include "Sudoku.hpp"
namespace Sudoku {
Solver::Solver(const Field& puzzle) :
    PuzzleSolver(DancingLinks::Solver(DLHelper::toDancingLinksList(puzzle))),
    Blocksize(puzzle.getBlocksize()) {}

std::optional<Field>
Solver::nextSolution() {
  auto exactCoverResult = PuzzleSolver.nextModel();
  if (!exactCoverResult) {
    return std::nullopt;
  }
  return DLHelper::fromDancingLinksList(*exactCoverResult, Blocksize);
}
} // namespace Sudoku
