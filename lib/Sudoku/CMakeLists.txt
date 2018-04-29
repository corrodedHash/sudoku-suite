add_library(Sudoku Field.cpp DLHelper.cpp Solver.cpp Generator.cpp)
target_include_directories(Sudoku PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Sudoku PUBLIC DancingLinks)

