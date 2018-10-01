#include "Sudoku/Field.hpp"
#include "Sudoku/Solver.hpp"

#include <benchmark/benchmark.h>

static Sudoku::Field
getField(int size) {
  Sudoku::Field field(size);
  for (int row = 0; row < size * size; ++row) {
    int column = (row % size) * size + (row / size);
    field.setCellValue(row, column, 1);
  }
  return field;
}
static void
BM_SudokuSolver_Solving(benchmark::State& state) {
  Sudoku::Field field = getField(state.range(0));
  for (auto _ : state) {
    state.PauseTiming();
    Sudoku::Solver solver(field);
    state.ResumeTiming();
    solver.nextSolution();
  }
}

static void
BM_SudokuSolver_Generation(benchmark::State& state) {
  Sudoku::Field field = getField(state.range(0));
  for (auto _ : state) {
    Sudoku::Solver solver(field);
  }
}

static void
BM_SudokuSolver_Whole(benchmark::State& state) {
  Sudoku::Field field = getField(state.range(0));
  for (auto _ : state) {
    Sudoku::Solver solver(field);
    solver.nextSolution();
  }
}

BENCHMARK(BM_SudokuSolver_Solving)->Arg(3)->Arg(4);
BENCHMARK(BM_SudokuSolver_Generation)->Arg(3)->Arg(4)->Arg(5)->Arg(6);
BENCHMARK(BM_SudokuSolver_Whole)->Arg(3)->Arg(4);
