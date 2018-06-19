#include "Sudoku/Generator.hpp"

#include "Sudoku/Field.hpp"

#include <iostream>

const int SudokuBlockSize = 3;
int
main(int /*argc*/, char** /*args*/) {
  auto x = Sudoku::Generator::generate(SudokuBlockSize);
  x.print(std::cout);
  std::cout << x.filledCellCount() << '\n';
  return 0;
}
