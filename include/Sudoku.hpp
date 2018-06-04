#pragma once
#include "DancingLinks/List.hpp"
#include "DancingLinks/Solver.hpp"

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

  /// @brief Print a string representation of sudoku field to stream
  ///
  /// @param stream Stream to print to
  void print(std::ostream& stream) const;
};

/// @brief Helper functions to translate sudoku to and from dancing links
/// representation
namespace DLHelper {
DancingLinks::List toDancingLinksList(const Field& field);
Field fromDancingLinksList(const std::vector<DancingLinks::Node*>& rowIndices,
                           int blocksize);
}; // namespace DLHelper

/// @brief Sudoku solver class
class Solver {
  DancingLinks::Solver PuzzleSolver;
  int Blocksize;

public:
  Solver(const Field& puzzle);

  /// @brief Returns a solution to the puzzle that has not yet been returned
  ///
  /// @return Either a completed sudoku field, or nullopt
  std::optional<Field> nextSolution();
};

/// @brief Generation functions for sudoku puzzles
namespace Generator {
/// @brief Generate a sudoku puzzle
Field generate(int blocksize);

/// @brief Generate an uncommitting sudoku puzzle
Field generateFieldStart(int blocksize);
} // namespace Generator

} // namespace Sudoku
