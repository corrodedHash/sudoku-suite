include( "ExternalCatch2" )
include( "Catch" )

set (TEST_SOURCES "")
add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
add_executable(testing main.cpp ${TEST_SOURCES})
target_link_libraries(testing Sudoku Catch2)

catch_discover_tests(testing)
