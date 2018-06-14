add_library(GeneralConfig INTERFACE)

# Set compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
  # Need to make Visual C++ conform standard
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Ze")
  # Default debug flags are OK
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(GeneralConfig INTERFACE "-fcolor-diagnostics")
  else()
    message(WARNING "Not compiling with clang, disabling colored diagnostics")
  endif()

  target_compile_options(GeneralConfig INTERFACE "-fno-omit-frame-pointer" "-fsave-optimization-record")
  if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    target_compile_options(GeneralConfig INTERFACE "-fsanitize=address,undefined"
      "-fsanitize-address-use-after-scope"
      "-fprofile-instr-generate" "-fcoverage-mapping")
    target_link_libraries(GeneralConfig INTERFACE "-fsanitize=address,undefined"
      "-fsanitize-address-use-after-scope"
      "-fprofile-instr-generate" "-fcoverage-mapping")
  endif()
  if("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")
    message(STATUS "Compiling with release")
    target_compile_options(GeneralConfig INTERFACE "-Ofast" "-mtune=native" "-march=native")
    target_link_libraries(GeneralConfig INTERFACE "-Ofast" "-mtune=native" "-march=native")
    target_compile_options(GeneralConfig INTERFACE "-flto")
    target_link_libraries(GeneralConfig INTERFACE "-flto")
  endif()

  if (${PROJECT_NAME}_ENABLE_FUZZER)
    target_compile_options(GeneralConfig INTERFACE "-fsanitize=fuzzer-no-link,address,undefined"
      "-fsanitize-address-use-after-scope")
    target_link_libraries(GeneralConfig INTERFACE "-fsanitize=fuzzer-no-link,address,undefined")
  endif()

  if (${PROJECT_NAME}_ENABLE_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=bugprone-*,clang-analyzer-*,-clang-analyzer-deadcode.DeadStores,misc-*,modernize-*,performance-*,readability-*")
  endif()
endif()

# Append system wide include directories
target_include_directories(GeneralConfig INTERFACE "${CMAKE_SOURCE_DIR}/include")

