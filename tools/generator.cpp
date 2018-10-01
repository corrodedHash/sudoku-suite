#include "Sudoku/Generator.hpp"

#include "Sudoku/Field.hpp"

#include <iostream>
#include <string>

int
main(int argc, char** args) {
  int maxFilledCells = 81;
  int sudokuBlockSize = 3;
  if (argc > 1) {
    sudokuBlockSize = std::stoi(args[1]);
  }
  if (argc > 2) {
    maxFilledCells = std::stoi(args[2]);
  }
  while (true) {
    auto x = Sudoku::Generator::generate(sudokuBlockSize);
    x.print(std::cout);
    std::cout << x.filledCellCount() << '\n';
    if (x.filledCellCount() <= maxFilledCells){
      break;
    }
  }
  return 0;
}
