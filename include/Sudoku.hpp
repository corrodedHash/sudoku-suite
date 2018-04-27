#pragma once
#include "DancingLinks.hpp"

#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace Sudoku {
/// @brief Represents sudoku game field
class Field {
  /// @brief Contains the values of each cell, starting at 1. 0 represents an
  /// unknown value
  std::vector<int> Grid;

  /// @brief How many cells are in a block / in a row / column
  int Blocksize;

  /// @brief Maps a coordinate on the sudoku field to the index of Grid vector
  int getIndex(int x, int y) const;
  /// @brief Maps Grid vector index to sudoku field coordinate
  std::pair<int, int> getCoord(int index);

public:
  Field(int blocksize);

  /// @brief Constant representing the unknown value
  const int UnsetValue = 0;

  /// @brief Calculates the biggest number that can be entered into a cell
  int getMaxNumber() const { return Blocksize * Blocksize; }

  int getBlocksize() const { return Blocksize; };

  int getCellValue(int x, int y) const { return Grid[getIndex(x, y)]; }

  void setCellValue(int x, int y, int value) {
    Grid[getIndex(x, y)] = value;
  }

  /// @brief Checks if every cell contains a non-unset value
  bool isSolved() const;

  /// @brief Returns a string representation of sudoku field
  std::string print() const;
};

/// @brief Helper class to translate sudoku to and from dancing links
/// representation
class DLHelper {
private:
  static int getRowId(int row, int col, int number, int blocksize);
  static std::tuple<int, int, int> getSudokuPos(int rowIndex, int blocksize);
  static std::pair<int, int> getDancingListSize(int blocksize);

public:
  static DancingLinks::List toDancingLinksList(const Field& field);
  static Field
  fromDancingLinksList(const std::vector<int>& rowIndices, int blocksize);
};
} // namespace Sudoku
