#include "Sudoku/Field.hpp"
#include "Sudoku/Solver.hpp"

#include <iostream>
#include <optional>
#include <string>

auto
main(int argc, char** args) -> int {
  int SudokuBlockSize = 3;
  if (argc >= 2) {
    SudokuBlockSize = std::stoi(args[1]);
  }

  Sudoku::Solver solver((Sudoku::Field(SudokuBlockSize)));

  while (auto model = solver.nextSolution()) {
    model->print(std::cout);
    std::cout << '\n';
    char x = 0;
    std::cin >> x;
  }
  return 0;
}
