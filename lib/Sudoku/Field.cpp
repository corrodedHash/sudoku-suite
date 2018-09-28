#include "Sudoku/Field.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

namespace Sudoku {
Field::Field(int blocksize) :
    Blocksize(blocksize),
    Grid(std::vector<int>(getMaxNumber() * getMaxNumber())){};

bool
Field::operator==(const Field& other) const {
  return (Blocksize == other.Blocksize) && (Grid.size() == other.Grid.size()) &&
         (Grid == other.Grid);
}

int
Field::getIndex(int x, int y) const {
  assert(x < getMaxNumber());
  assert(y < getMaxNumber());
  return y * getMaxNumber() + x;
}

bool
Field::filled() const {
  return std::none_of(std::begin(Grid), std::end(Grid),
                      [](auto x) { return x == 0; });
}

bool
Field::rowsCorrect() const {
  std::vector<bool> numbers(getMaxNumber(), false);
  for (int row = 0; row < getMaxNumber(); ++row) {
    for (int column = 0; column < getMaxNumber(); ++column) {
      if (getCellValue(row, column) == 0) {
        continue;
      }
      if (numbers.at(getCellValue(row, column) - 1)) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = true;
    }
    std::fill(std::begin(numbers), std::end(numbers), false);
  }
  return true;
}

bool
Field::columnsCorrect() const {
  std::vector<bool> numbers(getMaxNumber(), false);
  for (int column = 0; column < getMaxNumber(); ++column) {
    for (int row = 0; row < getMaxNumber(); ++row) {
      if (getCellValue(row, column) == 0) {
        continue;
      }
      if (numbers.at(getCellValue(row, column) - 1)) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = true;
    }
    std::fill(std::begin(numbers), std::end(numbers), false);
  }
  return true;
}

bool
Field::blocksCorrect() const {
  std::vector<bool> numbers(getMaxNumber(), false);
  for (int block = 0; block < getMaxNumber(); ++block) {
    for (int blockcell = 0; blockcell < getMaxNumber(); ++blockcell) {
      int row = (block / getBlocksize()) * getBlocksize() +
                blockcell / getBlocksize();
      int column = (block % getBlocksize()) * getBlocksize() +
                   blockcell % getBlocksize();
      if (getCellValue(row, column) == 0) {
        continue;
      }
      if (numbers.at(getCellValue(row, column) - 1)) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = true;
    }
    std::fill(std::begin(numbers), std::end(numbers), false);
  }
  return true;
}

bool
Field::correct() const {
  return rowsCorrect() && columnsCorrect() && blocksCorrect();
}

int
Field::filledCellCount() const {
  return std::count_if(std::begin(Grid), std::end(Grid),
                       [](auto x) { return x != 0; });
}

void
Field::print(std::ostream& stream) const {
  int curColumn = 0;
  int padSize = std::to_string(getMaxNumber()).size();
  for (auto cell : Grid) {
    stream << std::setw(padSize) << std::setfill(' ') << cell << " ";
    if (++curColumn >= getMaxNumber()) {
      stream << '\n';
      curColumn = 0;
    }
  }
}

} // namespace Sudoku
