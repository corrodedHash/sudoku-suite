add_executable(enumerator enumerator.cpp)
target_link_libraries(enumerator PRIVATE Core GeneralConfig)

add_executable(generator generator.cpp)
target_link_libraries(generator PRIVATE Core GeneralConfig)

add_executable(ycm_helper ycm_helper.cpp)
target_link_libraries(ycm_helper PRIVATE Core GeneralConfig)
