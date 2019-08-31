include( "boilerplate/fuzzer" )

target_sources(fuzzer PRIVATE main.cpp)
target_link_libraries(fuzzer PRIVATE Core)
