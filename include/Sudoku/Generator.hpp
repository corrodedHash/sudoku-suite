#pragma once
#include "Sudoku/Field.hpp"

namespace Sudoku::Generator {
/// @brief Generate a sudoku puzzle
auto generate(int blocksize) -> Field;
} // namespace Sudoku
