#include <cassert>

namespace Sudoku {
Field::Field(int blocksize) {
  Blocksize = blocksize;
  Grid = std::vector<int>(getMaxNumber() * getMaxNumber());
};

int Field::getMaxNumber() const { return Blocksize * Blocksize; }

int Field::getIndex(int x, int y) const {
  assert(x < getMaxNumber());
  assert(y < getMaxNumber());
  return y * getMaxNumber() + x;
}

int getCellValue(int x, int y) const { return Grid[getIndex(x, y)]; }

void setCellValue(int x, int y, int value) { Grid[getIndex(x, y)] = value; }
} // namespace Sudoku
