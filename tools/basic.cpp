#include "DancingLinks.hpp"
#include "Sudoku.hpp"

#include <iostream>

const int SudokuBlockSize = 1;
int
main(int /*argc*/, char** /*args*/) {
  DancingLinks::Solver solver(
      Sudoku::DLHelper::toDancingLinksList(Sudoku::Field(SudokuBlockSize)));

  while (auto model = solver.nextModel()) {
    std::cout << Sudoku::DLHelper::fromDancingLinksList(*model, SudokuBlockSize)
                     .print();
    char x;
    std::cin >> x;
  }
  return 0;
}
