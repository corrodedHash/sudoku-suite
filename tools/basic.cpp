#include "DancingLinks.hpp"
#include "Sudoku.hpp"
#include <iostream>

const int SudokuBlockSize = 3;
int
main(int /*argc*/, char** /*args*/) {
  std::unique_ptr<DancingLinks::List> l =
      Sudoku::DLHelper::toDancingLinksList(Sudoku::Field(SudokuBlockSize));
  DancingLinks::Solver s(std::move(l));
  while (auto model = s.nextModel()) {
    std::cout << Sudoku::DLHelper::fromDancingLinksList(*model, SudokuBlockSize)
                     .print();
    char x;
    std::cin >> x;
  }
  std::cout << "hola\n";
  return 0;
}
