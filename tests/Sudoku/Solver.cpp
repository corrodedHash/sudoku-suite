#include <catch2/catch.hpp>
#include <iostream>
#include <optional>
#include <vector>
#include <sstream>

#include "Sudoku/Field.hpp"
#include "Sudoku/Generator.hpp"
#include "Sudoku/Solver.hpp"

TEST_CASE("Solving a puzzle") {
  Sudoku::Field sudokuPuzzle = Sudoku::Generator::generate(3);
  REQUIRE_FALSE(sudokuPuzzle.filled());
  REQUIRE(sudokuPuzzle.correct());
  Sudoku::Solver sudokuSolver(sudokuPuzzle);
  auto sudokuResult = sudokuSolver.nextSolution();
  REQUIRE(sudokuResult);
  REQUIRE(sudokuResult->correct());
  REQUIRE(sudokuResult->filled());
  REQUIRE_FALSE(sudokuPuzzle == *sudokuResult);
  sudokuResult = sudokuSolver.nextSolution();
  REQUIRE_FALSE(sudokuResult);
}

TEST_CASE("Detecting incorrect puzzles") {
  SECTION("Detect incorrect row") {
    Sudoku::Field sudokuPuzzle(2);
    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        sudokuPuzzle.setCellValue(row, col, col + 1);
      }
    }
    REQUIRE(sudokuPuzzle.filled());
    REQUIRE_FALSE(sudokuPuzzle.correct());
  }
  SECTION("Detect incorrect column") {
    Sudoku::Field sudokuPuzzle(2);
    for (int col = 0; col < 4; ++col) {
      for (int row = 0; row < 4; ++row) {
        sudokuPuzzle.setCellValue(row, col, row + 1);
      }
    }
    REQUIRE(sudokuPuzzle.filled());
    REQUIRE_FALSE(sudokuPuzzle.correct());
  }
  SECTION("Detect incorrect block") {
    Sudoku::Field sudokuPuzzle(3);
    const std::vector<int> values{
        1, 5, 3, 7, 6, 4, 9, 2, 8, 7, 6, 9, 8, 5, 3, 4, 1, 2, 2, 3, 1,
        4, 9, 5, 8, 7, 6, 9, 7, 8, 3, 2, 6, 1, 5, 4, 4, 8, 6, 5, 1, 2,
        7, 9, 3, 5, 4, 7, 2, 8, 1, 6, 3, 9, 3, 9, 4, 1, 7, 8, 2, 6, 5,
        6, 2, 5, 9, 4, 7, 3, 8, 1, 8, 1, 2, 6, 3, 9, 5, 4, 7};
    for (int col = 0; col < 9; ++col) {
      for (int row = 0; row < 9; ++row) {
        sudokuPuzzle.setCellValue(row, col, values.at(row * 9 + col));
      }
    }
    REQUIRE(sudokuPuzzle.filled());
    REQUIRE_FALSE(sudokuPuzzle.correct());
  }
}

TEST_CASE("Print field") {
  Sudoku::Field sudokuPuzzle(2);
  std::stringstream dummy;
  sudokuPuzzle.print(dummy);
}
