#include "DancingLinks.hpp"
#include "Sudoku.hpp"

#include <iostream>

const int SudokuBlockSize = 3;
int
main(int /*argc*/, char** /*args*/) {
  std::cout << Sudoku::Field::generate(SudokuBlockSize).print();
  return 0;
}
