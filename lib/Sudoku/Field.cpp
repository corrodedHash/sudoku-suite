#include "Sudoku.hpp"

#include <cassert>
#include <sstream>

namespace Sudoku {
Field::Field(int blocksize) {
  Blocksize = blocksize;
  Grid = std::vector<int>(getMaxNumber() * getMaxNumber());
};

bool
Field::operator==(const Field& other) {
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
  for (auto x : Grid) {
    if (x == 0) {
      return false;
    }
  }
  return true;
}

bool
Field::isCorrect() const {
  std::vector<bool> numbers(getMaxNumber(), false);
  bool currentFlag = true;
  // Check rows
  for (int row = 0; row < getMaxNumber(); ++row) {
    for (int column = 0; column < getMaxNumber(); ++column) {
      if (numbers[getCellValue(row, column)] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column)] = currentFlag;
    }
    currentFlag = !currentFlag;
  }

  // Check column
  for (int column = 0; column < getMaxNumber(); ++column) {
    for (int row = 0; row < getMaxNumber(); ++row) {
      if (numbers[getCellValue(row, column)] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column)] = currentFlag;
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
      if (numbers[getCellValue(row, column)] == currentFlag) {
        return false;
      }
      numbers[getCellValue(row, column)] = currentFlag;
    }
    currentFlag = !currentFlag;
  }
  return true;
}

std::string
Field::print() const {
  int curColumn = 0;
  std::stringstream result;
  for (auto cell : Grid) {
    result << cell << " ";
    if (++curColumn >= getMaxNumber()) {
      result << '\n';
      curColumn = 0;
    }
  }
  return result.str();
}

} // namespace Sudoku
