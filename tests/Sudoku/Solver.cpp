#include "Sudoku.hpp"
#include "catch.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Solving a puzzle") {
  Sudoku::Field sudokuPuzzle = Sudoku::Generator::generate(3);
  REQUIRE_FALSE(sudokuPuzzle.isSolved());
  Sudoku::Solver sudokuSolver(sudokuPuzzle);
  auto sudokuResult = sudokuSolver.nextSolution();
  REQUIRE(sudokuResult);
  REQUIRE(sudokuResult->isSolved());
  REQUIRE(sudokuResult->isCorrect());
  REQUIRE_FALSE(sudokuPuzzle == *sudokuResult);
  sudokuResult = sudokuSolver.nextSolution();
  REQUIRE_FALSE(sudokuResult);
}

TEST_CASE("Detecting incorrect puzzles") {
  Sudoku::Field sudokuPuzzle(2);
  SECTION("Detect incorrect row") {
    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        sudokuPuzzle.setCellValue(row, col, col);
      }
    }
    REQUIRE_FALSE(sudokuPuzzle.isCorrect());
  }
  SECTION("Detect incorrect column") {
    for (int col = 0; col < 4; ++col) {
      for (int row = 0; row < 4; ++row) {
        sudokuPuzzle.setCellValue(row, col, row);
      }
    }
    REQUIRE_FALSE(sudokuPuzzle.isCorrect());
  }
}

TEST_CASE("Print field"){
  Sudoku::Field sudokuPuzzle(2);
  std::stringstream dummy;
  sudokuPuzzle.print(dummy);
}
