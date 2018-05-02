add_executable(benchmarks main.cpp SudokuSolver.cpp)

target_include_directories(benchmarks PRIVATE ${GOOGLEBENCH_INCLUDE} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(benchmarks GoogleBench Sudoku)
