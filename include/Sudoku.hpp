#pragma once
#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include "DancingLinks.hpp"

namespace Sudoku {
class Field {
  std::vector<int> Grid;

  int Blocksize;

  int getIndex(int x, int y) const;
  std::pair<int, int> getCoord(int index);

public:
  Field(int blocksize);

  const int UnsetValue = 0;
  const int MinNumber = 1;
  int getMaxNumber() const;
  int getBlocksize() const { return Blocksize; };

  int getCellValue(int x, int y) const;
  void setCellValue(int x, int y, int value);

  bool isSolved();

  std::string print() const;
};

class DLHelper {
private:
  static int getColId(int row, int col, int number, int blocksize);
  static std::tuple<int, int, int> getSudokuPos(int rowIndex, int blocksize);
  static std::pair<int, int> getDancingListSize(int blocksize);

public:
  static DancingLinks::List toDancingLinksList(const Field& field);
  static Field fromDancingLinksList(const std::vector<int> rowIndices, int blocksize);
};
} // namespace Sudoku
