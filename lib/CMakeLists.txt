file(WRITE null.cpp "")

add_library(Core STATIC null.cpp)
target_link_libraries(Core PRIVATE GeneralConfig SanitizerConfig)

add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
