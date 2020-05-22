if (NOT ${PROJECT_NAME}_BUILD_TESTS)
  return()
endif()

include( "boilerplate/testing" )

target_sources(testing PRIVATE main.cpp)
target_link_libraries(testing PRIVATE Core)

add_subdirectory(DancingLinks)
add_subdirectory(Sudoku)
