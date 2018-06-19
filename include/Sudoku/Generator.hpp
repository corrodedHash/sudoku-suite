#pragma once
#include "Sudoku/Field.hpp"

namespace Sudoku {
/// @brief Generation functions for sudoku puzzles
namespace Generator {
/// @brief Generate a sudoku puzzle
Field generate(int blocksize);
} // namespace Generator
} // namespace Sudoku
