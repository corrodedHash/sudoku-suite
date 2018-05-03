cmake_minimum_required(VERSION 3.3.2)
project(SudokuSuite LANGUAGES CXX DESCRIPTION "Program suite to generate and solve sudokus of any size")


# Set cache options
set(${PROJECT_NAME}_ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(${PROJECT_NAME}_ENABLE_FUZZER OFF CACHE BOOL "Enable fuzzing")
set(${PROJECT_NAME}_ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")
set(${PROJECT_NAME}_ENABLE_TIDY OFF CACHE BOOL "Enable clang-tidy")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
  # Need to make Visual C++ conform standard
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ze")
  # Default debug flags are OK
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
  if (${PROJECT_NAME}_ENABLE_FUZZER)
    string( APPEND CMAKE_CXX_FLAGS " -fsanitize-coverage=trace-pc-guard")
    string( APPEND CMAKE_CXX_FLAGS " -fprofile-instr-generate -fcoverage-mapping")
  endif()
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    string (APPEND CMAKE_CXX_FLAGS " -fcolor-diagnostics")
  else()
    message(WARNING "Not compiling with clang, disabling colored diagnostics")
  endif()

  string (APPEND CMAKE_CXX_FLAGS " -fno-omit-frame-pointer")
  #string (APPEND CMAKE_CXX_FLAGS " -flto=thin")
  #string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
  #string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize-address-use-after-scope")
  string (APPEND CMAKE_CXX_FLAGS_DEBUG " -fprofile-instr-generate -fcoverage-mapping")
  string (APPEND CMAKE_CXX_FLAGS_RELEASE " -Ofast -mtune=native -march=native")

  if (${PROJECT_NAME}_ENABLE_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=bugprone-*,clang-analyzer-*,-clang-analyzer-deadcode.DeadStores,misc-*,modernize-*,performance-*,readability-*")
  endif()
endif()

# Append system wide include directories
include_directories("${CMAKE_SOURCE_DIR}/include")

### END SETUP ###

add_subdirectory(lib)
add_subdirectory(tools)

if (${PROJECT_NAME}_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (${PROJECT_NAME}_ENABLE_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if (${PROJECT_NAME}_ENABLE_FUZZER)
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
