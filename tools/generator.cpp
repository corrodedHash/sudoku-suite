#include "Sudoku/Generator.hpp"

#include "Sudoku/Field.hpp"

#include <iostream>

const int SudokuBlockSize = 3;
int
main(int /*argc*/, char** /*args*/) {
  Sudoku::Generator::generate(SudokuBlockSize).print(std::cout);
  return 0;
}
