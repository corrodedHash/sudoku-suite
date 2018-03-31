add_executable(testing main.cpp Solver.cpp)

target_link_libraries(testing Sudoku)
target_include_directories(testing PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME main_test COMMAND testing)
