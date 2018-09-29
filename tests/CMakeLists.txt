include( "ExternalCatch2" )

set (TEST_SOURCES "")
add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
add_executable(testing main.cpp ${TEST_SOURCES})
target_link_libraries(testing PRIVATE GeneralConfig Sudoku Catch2::Catch2)
get_property(catch_includes TARGET Catch2::Catch2 PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "catch_includes: ${catch_includes}")

add_custom_target(test ./testing)

add_custom_target(test_cov ./testing
  COMMAND llvm-profdata merge -o testing.profdata default.profraw
  COMMAND llvm-cov report --use-color --instr-profile testing.profdata ./testing
  COMMAND rm -i -rf testing_cov_report
  COMMAND llvm-cov show --use-color --format=html -o testing_cov_report --instr-profile testing.profdata ./testing)
