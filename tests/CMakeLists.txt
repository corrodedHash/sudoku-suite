include( "ExternalCatch2" )
include( "Catch" )

set (TEST_SOURCES "")
add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
add_executable(testing main.cpp ${TEST_SOURCES})
target_link_libraries(testing PRIVATE GeneralConfig Sudoku Catch2::Catch2)
get_property(catch_includes TARGET Catch2::Catch2 PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "catch_includes: ${catch_includes}")

catch_discover_tests(testing)
