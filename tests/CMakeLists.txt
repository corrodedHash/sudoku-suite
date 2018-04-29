include( "Catch" )

add_executable(testing main.cpp Solver.cpp)

target_link_libraries(testing Sudoku Catch2)
#target_include_directories(testing PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

catch_discover_tests(testing)
