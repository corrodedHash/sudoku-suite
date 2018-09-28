#pragma once
#include <ostream>
#include <utility>
#include <vector>

namespace Sudoku {
/// @brief Represents sudoku game field
class Field {

  /// @brief How many cells are in a block / row / column
  int Blocksize;

  /// @brief Contains the values of each cell, starting at 1. 0 represents an
  /// unknown value
  std::vector<int> Grid;

  /// @brief Maps a coordinate on the sudoku field to the index of Grid vector
  int getIndex(int x, int y) const;
  /// @brief Maps Grid vector index to sudoku field coordinate
  std::pair<int, int> getCoord(int index);

public:
  /// @brief Create a Sudoku Field with given blockwidth
  ///
  /// @param blocksize The width of a block. The field will be blocksize *
  /// blocksize wide
  Field(int blocksize);

  /// @brief Calculates the biggest number that can be entered into a cell
  int getMaxNumber() const { return Blocksize * Blocksize; }

  /// @brief Return blocksize
  int getBlocksize() const { return Blocksize; };

  /// @brief Get cell at given coordinate
  int getCellValue(int x, int y) const { return Grid[getIndex(x, y)]; }

  /// @brief Set cell at given coordinate
  void setCellValue(int x, int y, int value) { Grid[getIndex(x, y)] = value; }

  /// @brief Checks if every cell contains a non-unset value
  bool filled() const;

  /// @brief Checks that every row, column and block only has each number once
  /// and is filled
  bool correct() const;

  /// @return Amount of cells that are not 0
  int filledCellCount() const;

  /// @brief Both fields are same size, and all cells have the same entries
  bool operator==(const Field& other) const;

  /// @brief The fields are not equivalent
  bool operator!=(const Field& other) const { return !(*this == other); }

  /// @brief Print a string representation of sudoku field to stream
  ///
  /// @param stream Stream to print to
  void print(std::ostream& stream) const;
};
} // namespace Sudoku
