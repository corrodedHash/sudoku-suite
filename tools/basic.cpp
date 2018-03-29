#include "DancingLinks.hpp"
#include <iostream>

const int SudokuBlockSize = 3;
int main(int /*argc*/, char** /*args*/)
{
  DancingLinks::Solver s(toDancingLinksList<SudokuBlockSize>(createExactCover<SudokuBlockSize>()));
  while (s.nextModel()) {
    drawSudoku<SudokuBlockSize>(s);
    std::cout << s.Removed.size() << '\n';
    return 0;
  }
  std::cout << "hola\n";
  return 0;
}

