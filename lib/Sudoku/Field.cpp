#include "Sudoku.hpp"

#include <cassert>
#include <sstream>

namespace Sudoku {
Field::Field(int blocksize) {
  Blocksize = blocksize;
  Grid = std::vector<int>(getMaxNumber() * getMaxNumber());
};

int
Field::getIndex(int x, int y) const {
  assert(x < getMaxNumber());
  assert(y < getMaxNumber());
  return y * getMaxNumber() + x;
}

bool
Field::isSolved() const {
  for (auto x : Grid) {
    if (x == UnsetValue) {
      return false;
    }
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
