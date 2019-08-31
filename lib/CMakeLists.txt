add_library(Core STATIC)
target_link_libraries(Core PRIVATE GeneralConfig)

add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
