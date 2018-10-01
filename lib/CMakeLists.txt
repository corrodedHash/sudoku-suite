set (LIB_SOURCES "")
add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)

add_library(Core STATIC ${LIB_SOURCES})
target_link_libraries(Core PRIVATE GeneralConfig)
