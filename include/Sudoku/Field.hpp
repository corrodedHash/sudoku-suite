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
  [[nodiscard]] auto getIndex(int x, int y) const -> int;
  /// @brief Maps Grid vector index to sudoku field coordinate
  auto getCoord(int index) -> std::pair<int, int>;

public:
  /// @brief Create a Sudoku Field with given blockwidth
  ///
  /// @param blocksize The width of a block. The field will be blocksize *
  /// blocksize wide
  Field(int blocksize);

  /// @brief Calculates the biggest number that can be entered into a cell
  [[nodiscard]] auto getMaxNumber() const -> int { return Blocksize * Blocksize; }

  /// @brief Return blocksize
  [[nodiscard]] auto getBlocksize() const -> int { return Blocksize; };

  /// @brief Get cell at given coordinate
  [[nodiscard]] auto getCellValue(int x, int y) const -> int { return Grid[getIndex(x, y)]; }

  /// @brief Set cell at given coordinate
  void setCellValue(int x, int y, int value) { Grid[getIndex(x, y)] = value; }

  /// @brief Checks if every cell contains a non-unset value
  [[nodiscard]] auto filled() const -> bool;

  /// @brief Checks that every row only has each number once
  [[nodiscard]] auto rowsCorrect() const -> bool;

  /// @brief Checks that every column only has each number once
  [[nodiscard]] auto columnsCorrect() const -> bool;

  /// @brief Checks that every block only has each number once
  [[nodiscard]] auto blocksCorrect() const -> bool;

  /// @brief Checks that every row, column and block only has each number once
  /// and is filled
  [[nodiscard]] auto correct() const -> bool;

  /// @return Amount of cells that are not 0
  [[nodiscard]] auto filledCellCount() const -> int;

  /// @brief Both fields are same size, and all cells have the same entries
  auto operator==(const Field& other) const -> bool;

  /// @brief The fields are not equivalent
  auto operator!=(const Field& other) const -> bool { return !(*this == other); }

  /// @brief Print a string representation of sudoku field to stream
  ///
  /// @param stream Stream to print to
  void print(std::ostream& stream) const;
};
} // namespace Sudoku
