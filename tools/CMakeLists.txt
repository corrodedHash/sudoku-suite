add_executable(enumerator enumerator.cpp)
target_link_libraries(enumerator PRIVATE Sudoku GeneralConfig)

add_executable(generator generator.cpp)
target_link_libraries(generator PRIVATE Sudoku GeneralConfig)
