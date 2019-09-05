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

  target_compile_options(GeneralConfig INTERFACE -fno-omit-frame-pointer)
  target_compile_options(GeneralConfig INTERFACE -Wall -Wextra -Wpedantic)
  target_link_options(GeneralConfig INTERFACE -fno-omit-frame-pointer)
  target_link_options(GeneralConfig INTERFACE -Wall -Wextra -Wpedantic)

  target_include_directories(GeneralConfig INTERFACE ${CMAKE_SOURCE_DIR}/include)

  if(${PROJECT_NAME}_COVERAGE)
    target_compile_options(GeneralConfig INTERFACE
      "-fprofile-instr-generate" "-fcoverage-mapping")
    target_link_options(GeneralConfig INTERFACE
      "-fprofile-instr-generate" "-fcoverage-mapping")

  endif()

  if(${PROJECT_NAME}_GCOV)
    target_compile_options(GeneralConfig INTERFACE
      "-fprofile-arcs" "-ftest-coverage")
    target_link_options(GeneralConfig INTERFACE
      "-fprofile-arcs" "-ftest-coverage")
  endif()

  if(${PROJECT_NAME}_USE_LLD)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
      target_link_options(GeneralConfig INTERFACE
        "-fuse-ld=lld" "-Wl,--threads")
    else()
      message(WARNING "Won't use lld without clang")
    endif()
  endif()

  if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")

    message(STATUS "Compiling with release")
    target_compile_options(GeneralConfig INTERFACE "-Ofast"
      "-mtune=native" "-march=native")
    target_link_options(GeneralConfig INTERFACE "-Ofast"
      "-mtune=native" "-march=native")
    target_compile_options(GeneralConfig INTERFACE "-flto")
    target_link_options(GeneralConfig INTERFACE "-flto")

  endif()
endif()

# Append project wide include directories
target_include_directories(GeneralConfig INTERFACE "${CMAKE_SOURCE_DIR}/include")
