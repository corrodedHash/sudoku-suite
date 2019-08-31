include( "boilerplate/testing" )

target_sources(testing PRIVATE main.cpp)
target_link_libraries(testing PRIVATE Core)

add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
