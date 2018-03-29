add_library(dlsudoku List.cpp ListGenesisNode.cpp ListNode.cpp Solver.cpp)
target_include_directories(dlsudoku PUBLIC ${CMAKE_SOURCE_DIR}/include)

