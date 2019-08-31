include( "boilerplate/benchmark" )

target_sources(benchmarks PRIVATE main.cpp SudokuSolver.cpp)
target_link_libraries(benchmarks PRIVATE Core)
