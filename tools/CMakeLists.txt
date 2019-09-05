add_executable(enumerator enumerator.cpp)
target_link_libraries(enumerator PRIVATE Core GeneralConfig SanitizerConfig)

add_executable(generator generator.cpp)
target_link_libraries(generator PRIVATE Core GeneralConfig SanitizerConfig)
