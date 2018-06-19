#include "Sudoku/Generator.hpp"

#include "Sudoku/Field.hpp"
#include "Sudoku/Solver.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <utility>

namespace Sudoku::Generator {
Field
generateFieldStart(int blocksize) {
  Field result(blocksize);
  int maxNum = blocksize * blocksize;
  std::srand(std::time(nullptr));
  for (int row = 0; row < blocksize; ++row) {
    for (int column = 0; column < blocksize; ++column) {
      result.setCellValue(column * blocksize + (column + row) % blocksize,
                          row * blocksize + column, (std::rand() % maxNum) + 1);
    }
  }
  return result;
}

static int
countSetCells(const Field& field) {
  int count = 0;
  for (int row = 0; row < field.getMaxNumber(); ++row) {
    for (int column = 0; column < field.getMaxNumber(); ++column) {
      if (field.getCellValue(column, row) > 0) {
        ++count;
      }
    }
  }
  return count;
}

static Field
getMedianField(const Field& lower, const Field& upper) {
  assert(lower.getBlocksize() == upper.getBlocksize());

  int lowerCount = countSetCells(lower);
  int upperCount = countSetCells(upper);
  int resultDelta = (upperCount - lowerCount) / 2;

  assert(lowerCount <= upperCount);
  assert(resultDelta >= 0);

  Field result = upper;
  for (int row = 0; row < upper.getMaxNumber(); ++row) {
    for (int column = 0; column < upper.getMaxNumber(); ++column) {
      if (resultDelta == 0) {
        break;
      }
      if ((lower.getCellValue(column, row) == 0) &&
          (result.getCellValue(column, row) > 0)) {
        result.setCellValue(column, row, 0);
      }
      --resultDelta;
    }
  }
  return result;
}

Field
generate(int blocksize) {
  Field lowerBound = generateFieldStart(blocksize);
  Solver sudokuSolver(lowerBound);
  auto result = sudokuSolver.nextSolution();
  assert(result);
  Field upperBound = std::move(*result);
  for (int i = 0; true; ++i) {
    assert(i < blocksize * blocksize * blocksize * blocksize);
    Field medianField = getMedianField(lowerBound, upperBound);
    assert(medianField != lowerBound);
    if (medianField == upperBound) {
      return upperBound;
    }
    Solver loopSudokuSolver(medianField);

    // Check if the puzzle has a unique solution
    auto firstSolution = loopSudokuSolver.nextSolution();
    assert(firstSolution);
    if (loopSudokuSolver.nextSolution()) {
      lowerBound = medianField;
    } else {
      upperBound = medianField;
    }
  }
}
} // namespace Sudoku::Generator
