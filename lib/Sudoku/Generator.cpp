#include "Sudoku.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace Sudoku {
Field
getRandomFieldStart(int blocksize) {
  Field result(blocksize);
  std::srand(std::time(nullptr));
  for (int row = 0; row < blocksize; ++row) {
    for (int column = 0; column < blocksize; ++column) {
      result.setCellValue((column * blocksize + column + row) % blocksize,
                          row * blocksize + column,
                          (std::rand() % blocksize) + 1);
    }
  }
  return result;
}

int
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

Field
getMedianField(const Field& lower, const Field& upper) {
  std::cout << lower.getBlocksize() << " " << upper.getBlocksize() << '\n';
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
Field::generate(int blocksize) {
  Field lowerBound = getRandomFieldStart(blocksize);
  std::cout << lowerBound.print() << '\n';
  Solver sudokuSolver(getRandomFieldStart(blocksize));
  auto result = sudokuSolver.nextSolution();
  assert(result);
  Field upperBound = *result;
  while (true) {
    Field medianField = getMedianField(lowerBound, upperBound);
    if (medianField == upperBound) {
      return upperBound;
    }
    new (&sudokuSolver) Solver(medianField);
    assert(sudokuSolver.nextSolution());
    if (sudokuSolver.nextSolution()) {
      lowerBound = medianField;
    } else {
      upperBound = medianField;
    }
  }
}
} // namespace Sudoku
