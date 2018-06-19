#pragma once
#include <ostream>
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

  /// @brief Calculates the biggest number that can be entered into a cell
  int getMaxNumber() const { return Blocksize * Blocksize; }

  int getBlocksize() const { return Blocksize; };

  int getCellValue(int x, int y) const { return Grid[getIndex(x, y)]; }

  void setCellValue(int x, int y, int value) { Grid[getIndex(x, y)] = value; }

  /// @brief Checks if every cell contains a non-unset value
  bool isSolved() const;

  /// @brief Checks that every row, column and block only has each number once
  bool isCorrect() const;

  bool operator==(const Field& other) const;
  bool operator!=(const Field& other) const { return !(*this == other); }

  /// @brief Print a string representation of sudoku field to stream
  ///
  /// @param stream Stream to print to
  void print(std::ostream& stream) const;
};
} // namespace Sudoku
