add_executable(testing main.cpp fractalgen.cpp whole.cpp linalg.cpp random.cpp)

target_link_libraries(testing corelib)
target_include_directories(testing PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME main_test COMMAND testing)
