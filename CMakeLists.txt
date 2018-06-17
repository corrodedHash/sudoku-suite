cmake_minimum_required(VERSION 3.3.2)
project(SudokuSuite LANGUAGES CXX DESCRIPTION "Program suite to generate and solve sudokus of any size")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Set cache options
set(${PROJECT_NAME}_TESTS OFF CACHE BOOL "Enable tests")
set(${PROJECT_NAME}_FUZZER OFF CACHE BOOL "Enable fuzzing")
set(${PROJECT_NAME}_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")
set(${PROJECT_NAME}_TIDY OFF CACHE BOOL "Enable clang-tidy")
set(${PROJECT_NAME}_SANITIZER_ADDRESS OFF CACHE BOOL "Enable ASAN")
set(${PROJECT_NAME}_SANITIZER_MEMORY OFF CACHE BOOL "Enable MSAN")
set(${PROJECT_NAME}_SANITIZER_UB OFF CACHE BOOL "Enable UBSAN")
set(${PROJECT_NAME}_COVERAGE OFF CACHE BOOL "Enable coverage mapping")

include( "GeneralConfig" )

### END SETUP ###

add_subdirectory(lib)
add_subdirectory(tools)

if (${PROJECT_NAME}_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (${PROJECT_NAME}_TIDY)
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=bugprone-*,clang-analyzer-*,-clang-analyzer-deadcode.DeadStores,misc-*,modernize-*,performance-*,readability-*")
endif()

if (${PROJECT_NAME}_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if (${PROJECT_NAME}_FUZZER)
  add_subdirectory(fuzzer)
endif()

### END SOURCE FILES ###

# Add doxygen target
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)
# END SPECIAL TARGETS
