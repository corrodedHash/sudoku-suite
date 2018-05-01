#include "Sudoku.hpp"

#include <benchmark/benchmark.h>

static void
BM_SudokuSolver(benchmark::State& state) {
  Sudoku::Field field(3);
  field.setCellValue(0, 0, 1);
  field.setCellValue(1, 4, 1);
  field.setCellValue(2, 8, 1);
  field.setCellValue(3, 1, 1);
  field.setCellValue(4, 5, 1);
  field.setCellValue(5, 6, 1);
  field.setCellValue(6, 2, 1);
  field.setCellValue(7, 3, 1);
  field.setCellValue(8, 7, 1);
  for (auto _ : state) {
    Sudoku::Solver solver(field);
    solver.nextSolution();
  }
}
BENCHMARK(BM_SudokuSolver);
