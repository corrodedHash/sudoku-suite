include( "ExternalGoogleBenchmarks" )
add_executable(benchmarks main.cpp SudokuSolver.cpp)

target_include_directories(benchmarks PRIVATE ${GOOGLEBENCH_INCLUDE} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(benchmarks PRIVATE GoogleBench Sudoku)
target_link_libraries(benchmarks PUBLIC GeneralConfig)
