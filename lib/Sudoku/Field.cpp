#include "Sudoku.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace Sudoku {
Field::Field(int blocksize) {
  Blocksize = blocksize;
  Grid = std::vector<int>(getMaxNumber() * getMaxNumber());
};

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
Field::isSolved() const {
  return std::none_of(std::begin(Grid), std::end(Grid),
                      [](auto x) { return x == 0; });
}

bool
Field::isCorrect() const {
  std::vector<bool> numbers(getMaxNumber(), false);
  bool currentFlag = true;
  if (!isSolved()) {
    std::cout << "Warning: checked unsolved puzzle\n";
    return false;
  }
  // Check rows
  for (int row = 0; row < getMaxNumber(); ++row) {
    for (int column = 0; column < getMaxNumber(); ++column) {
      if (numbers[getCellValue(row, column) - 1] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = currentFlag;
    }
    currentFlag = !currentFlag;
  }

  // Check column
  for (int column = 0; column < getMaxNumber(); ++column) {
    for (int row = 0; row < getMaxNumber(); ++row) {
      if (numbers[getCellValue(row, column) - 1] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = currentFlag;
    }
    currentFlag = !currentFlag;
  }

  // Check block
  for (int block = 0; block < getMaxNumber(); ++block) {
    for (int blockcell = 0; blockcell < getMaxNumber(); ++blockcell) {
      int row = (block / getBlocksize()) * getBlocksize() +
                blockcell / getBlocksize();
      int column = (block % getBlocksize()) * getBlocksize() +
                   blockcell % getBlocksize();
      if (numbers[getCellValue(row, column) - 1] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column) - 1] = currentFlag;
    }
    currentFlag = !currentFlag;
  }
  return true;
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
