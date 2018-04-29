add_executable(basic basic.cpp)
target_link_libraries(basic PRIVATE Sudoku)

add_executable(generator generator.cpp)
target_link_libraries(generator PRIVATE Sudoku)
