add_subdirectory(lib)
add_subdirectory(tools)

if (${PROJECT_NAME}_TESTS)
  add_subdirectory(tests)
endif()

if (${PROJECT_NAME}_BENCHMARKS)
  add_subdirectory(benchmarks)
endif()

if (${PROJECT_NAME}_FUZZER)
  add_subdirectory(fuzzer)
endif()
