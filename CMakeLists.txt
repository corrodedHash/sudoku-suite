cmake_minimum_required(VERSION 3.3.2)
project(SudokuSuite LANGUAGES CXX DESCRIPTION "Program suite to generate and solve sudokus of any size")


# Set cache options
set(${PROJECT_NAME}_ENABLE_TESTS OFF CACHE BOOL "Enable tests")
set(${PROJECT_NAME}_ENABLE_FUZZER OFF CACHE BOOL "Enable fuzzing")
set(${PROJECT_NAME}_ENABLE_BENCHMARKS OFF CACHE BOOL "Enable benchmarks")
set(${PROJECT_NAME}_ENABLE_TIDY OFF CACHE BOOL "Enable clang-tidy")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

add_library(GeneralConfig INTERFACE)

# Set compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
  # Need to make Visual C++ conform standard
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ze")
  # Default debug flags are OK
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(GeneralConfig INTERFACE "-fcolor-diagnostics")
  else()
    message(WARNING "Not compiling with clang, disabling colored diagnostics")
  endif()

  target_compile_options(GeneralConfig INTERFACE "-fno-omit-frame-pointer")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(GeneralConfig INTERFACE "-fsanitize=address,undefined"
      "-fsanitize-address-use-after-scope"
      "-fprofile-instr-generate" "-fcoverage-mapping")
    target_link_libraries(GeneralConfig INTERFACE "-fsanitize=address,undefined"
      "-fsanitize-address-use-after-scope"
      "-fprofile-instr-generate" "-fcoverage-mapping")
  endif()
  string (APPEND CMAKE_CXX_FLAGS_RELEASE " -Ofast -mtune=native -march=native")

  if (${PROJECT_NAME}_ENABLE_FUZZER)
    target_compile_options(GeneralConfig INTERFACE "-fsanitize=fuzzer-no-link,address,undefined"
      "-fsanitize-address-use-after-scope")
    target_link_libraries(GeneralConfig INTERFACE "-fsanitize=fuzzer-no-link,address,undefined")
  endif()

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
