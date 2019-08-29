cmake_minimum_required(VERSION 3.3.2)
project(SudokuSuite LANGUAGES CXX DESCRIPTION "Program suite to generate and solve sudokus of any size")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include( "general/all")

### END SETUP ###

add_subdirectory(lib)
add_subdirectory(tools)

if (${PROJECT_NAME}_TESTS)
  add_subdirectory(tests)
endif()

if (${PROJECT_NAME}_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if (${PROJECT_NAME}_FUZZER)
  add_subdirectory(fuzzer)
endif()

### END SOURCE FILES ###
