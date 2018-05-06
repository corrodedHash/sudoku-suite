#include "DancingLinks.hpp"
#include "Sudoku.hpp"

#include <iostream>

int
main(int argc, char** args) {
  int SudokuBlockSize = 3;
  if (argc >= 2) {
    SudokuBlockSize = std::stoi(args[1]);
  }

  Sudoku::Solver solver((Sudoku::Field(SudokuBlockSize)));

  while (auto model = solver.nextSolution()) {
    model->print(std::cout);
    std::cout << '\n';
    char x;
    std::cin >> x;
  }
  return 0;
}
