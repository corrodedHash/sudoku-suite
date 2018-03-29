add_library(corelib DLList.cpp DLListGenesisNode.cpp DLListNode.cpp DLSolver.cpp)
target_include_directories(corelib PUBLIC ${CMAKE_SOURCE_DIR}/include)

