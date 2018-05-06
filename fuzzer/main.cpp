#include "Sudoku.hpp"

extern "C" int
LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
  if (Size < 1) {
    return 0 ;
  }
  int blocksize = (Data[0] % 4) + 1;
  Sudoku::Field field(blocksize);
  for (int i = 1, cell = 0;
       i < Size && cell < blocksize * blocksize * blocksize * blocksize;
       ++i, ++cell) {
    field.setCellValue(cell % (blocksize * blocksize),
                       cell / (blocksize * blocksize),
                       (Data[0] % (blocksize * blocksize)) + 1);
  }
  Sudoku::Solver solver(field);
  for (int i = 0; i < 10 && solver.nextSolution(); ++i) {
  }
  return 0;
}
