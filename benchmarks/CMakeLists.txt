if (NOT ${PROJECT_NAME}_BUILD_BENCHMARKS)
  return()
endif()

include( "boilerplate/benchmark" )

target_sources(benchmarks PRIVATE main.cpp SudokuSolver.cpp)
target_link_libraries(benchmarks PRIVATE Core GeneralConfig)
