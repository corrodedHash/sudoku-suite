#include "Sudoku/Generator.hpp"

#include "Sudoku/Field.hpp"
#include "Sudoku/Solver.hpp"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <random>
#include <utility>

namespace Sudoku::Generator {
static Field
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

static std::random_device rd;
static std::mt19937 g(rd());

static void
nullCellsStraight(const Field& lower, Field* field, int number) {
  assert(number >= 0);
  for (int row = 0; row < lower.getMaxNumber(); ++row) {
    for (int column = 0; column < lower.getMaxNumber(); ++column) {
      if (number == 0) {
        break;
      }
      if ((lower.getCellValue(column, row) == 0) &&
          (field->getCellValue(column, row) > 0)) {
        field->setCellValue(column, row, 0);
      }
      --number;
    }
  }
}

static void
nullCellsRandom(const Field& lower, Field* field, int number) {
  assert(number >= 0);
  std::vector<int> indices(lower.getMaxNumber() * lower.getMaxNumber());
  std::iota(std::begin(indices), std::end(indices), 0);
  std::shuffle(std::begin(indices), std::end(indices), g);
  for (auto index : indices) {
    if (number == 0) {
      return;
    }

    int row = index / lower.getMaxNumber();
    int column = index % lower.getMaxNumber();
    if ((lower.getCellValue(column, row) == 0) &&
        (field->getCellValue(column, row) > 0)) {
      field->setCellValue(column, row, 0);
    }
    --number;
  }
}

static Field
makeMedianField(const Field& lower, const Field& upper) {
  assert(lower.getBlocksize() == upper.getBlocksize());

  int lowerCount = lower.filledCellCount();
  int upperCount = upper.filledCellCount();
  assert(lowerCount <= upperCount);

  int resultDelta = (upperCount - lowerCount) / 2;

  Field result = upper;
  nullCellsRandom(lower, &result, resultDelta);
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
    Field medianField = makeMedianField(lowerBound, upperBound);
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
