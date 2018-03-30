add_library(sudoku Field.cpp DLHelper.cpp)
target_include_directories(sudoku PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(sudoku PUBLIC dlsudoku)

