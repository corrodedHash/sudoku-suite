#include "Sudoku.hpp"

#include <benchmark/benchmark.h>

static Sudoku::Field
getField() {
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
  return field;
}
static void
BM_SudokuSolver_Solving(benchmark::State& state) {
  Sudoku::Field field = getField();
  for (auto _ : state) {
    state.PauseTiming();
    Sudoku::Solver solver(field);
    state.ResumeTiming();
    solver.nextSolution();
  }
}

static void
BM_SudokuSolver_Generation(benchmark::State& state) {
  Sudoku::Field field = getField();
  for (auto _ : state) {
    Sudoku::Solver solver(field);
  }
}

static void
BM_SudokuSolver_Whole(benchmark::State& state) {
  Sudoku::Field field = getField();
  for (auto _ : state) {
    Sudoku::Solver solver(field);
    solver.nextSolution();
  }
}

BENCHMARK(BM_SudokuSolver_Solving);
BENCHMARK(BM_SudokuSolver_Generation);
BENCHMARK(BM_SudokuSolver_Whole);
