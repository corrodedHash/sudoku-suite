#include "DancingLinks.hpp"
#include "Sudoku.hpp"
#include <iostream>

const int SudokuBlockSize = 3;
int main(int /*argc*/, char** /*args*/) {
  DancingLinks::Solver s(Sudoku::DLHelper::toDancingLinksList(Sudoku::Field(SudokuBlockSize)));
  while (auto model = s.nextModel()) {
    std::cout << Sudoku::DLHelper::fromDancingLinksList(*model, SudokuBlockSize).print();
    char x;
    std::cin >> x;
  }
  std::cout << "hola\n";
  return 0;
}
