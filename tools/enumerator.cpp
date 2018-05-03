#include "DancingLinks.hpp"
#include "Sudoku.hpp"

#include <iostream>

int
main(int argc, char** args) {
  int SudokuBlockSize = 3;
  if (argc >= 2) {
    SudokuBlockSize = std::stoi(args[1]);
  }
  DancingLinks::Solver solver(
      Sudoku::DLHelper::toDancingLinksList(Sudoku::Field(SudokuBlockSize)));

  while (auto model = solver.nextModel()) {
    std::cout << Sudoku::DLHelper::fromDancingLinksList(*model, SudokuBlockSize)
                     .print();
    std::cout << '\n';
    char x;
    std::cin >> x;
  }
  return 0;
}
