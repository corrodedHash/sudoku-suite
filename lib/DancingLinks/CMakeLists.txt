add_library(DancingLinks List.cpp ListBuilder.cpp Solver.cpp Node.cpp)
target_include_directories(DancingLinks PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(DancingLinks PUBLIC GeneralConfig)

