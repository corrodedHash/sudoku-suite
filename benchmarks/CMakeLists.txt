include( "external/GoogleBenchmarks" )
add_executable(benchmarks main.cpp SudokuSolver.cpp)
target_link_libraries(benchmarks PRIVATE Core GeneralConfig)
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)
