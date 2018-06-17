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

  target_compile_options(GeneralConfig INTERFACE "-fno-omit-frame-pointer")

  if("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")

    set(SANITIZER_LIST "")
    if(${${PROJECT_NAME}_SANITIZER_ADDRESS})
      list(APPEND SANITIZER_LIST "address")
      target_compile_options(GeneralConfig INTERFACE
        "-fsanitize-address-use-after-scope")
      target_link_libraries(GeneralConfig INTERFACE
        "-fsanitize-address-use-after-scope")
    endif()

    if(${${PROJECT_NAME}_SANITIZER_UB})
      list(APPEND SANITIZER_LIST "undefined")
    endif()

    if(${${PROJECT_NAME}_SANITIZER_MEMORY})
      list(APPEND SANITIZER_LIST "memory")
      target_include_directories(GeneralConfig SYSTEM INTERFACE
        "${CMAKE_BINARY_DIR}/msan_llvm/build/include"
        "${CMAKE_BINARY_DIR}/msan_llvm/build/include/c++/v1")
      target_compile_options(GeneralConfig INTERFACE
        "-stdlib=libc++"
        "-fsanitize-memory-track-origins")
      target_link_libraries(GeneralConfig INTERFACE
        "-stdlib=libc++"
        "-fsanitize-memory-track-origins"
        "${CMAKE_BINARY_DIR}/msan_llvm/build/lib/libc++.so"
        "${CMAKE_BINARY_DIR}/msan_llvm/build/lib/libc++abi.so")
    endif()

    if(${PROJECT_NAME}_COVERAGE)

      target_compile_options(GeneralConfig INTERFACE
        "-fprofile-instr-generate" "-fcoverage-mapping")
      target_link_libraries(GeneralConfig INTERFACE
        "-fprofile-instr-generate" "-fcoverage-mapping")

    endif()

    if (${PROJECT_NAME}_FUZZER)

      list(APPEND SANITIZER_LIST "fuzzer-no-link")
      string(REPLACE ";" "," SANITIZER_STRING "${SANITIZER_LIST}" )
      target_compile_options(GeneralConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")
      target_link_libraries(GeneralConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")

      add_library(FuzzerConfig INTERFACE)
      target_link_libraries(FuzzerConfig INTERFACE GeneralConfig)

      list(REMOVE_ITEM SANITIZER_LIST "fuzzer-no-link")
      list(APPEND SANITIZER_LIST "fuzzer")
      string(REPLACE ";" "," SANITIZER_STRING "${SANITIZER_LIST}" )
      target_compile_options(FuzzerConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")
      target_link_libraries(FuzzerConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")

    else()

      string(REPLACE ";" "," SANITIZER_STRING "${SANITIZER_LIST}" )
      target_compile_options(GeneralConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")
      target_link_libraries(GeneralConfig INTERFACE
        "-fsanitize=${SANITIZER_STRING}")

    endif()

  elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RELEASE")

    message(STATUS "Compiling with release")
    target_compile_options(GeneralConfig INTERFACE "-Ofast"
      "-mtune=native" "-march=native")
    target_link_libraries(GeneralConfig INTERFACE "-Ofast"
      "-mtune=native" "-march=native")
    target_compile_options(GeneralConfig INTERFACE "-flto")
    target_link_libraries(GeneralConfig INTERFACE "-flto")

  endif()
endif()

# Append system wide include directories
target_include_directories(GeneralConfig INTERFACE "${CMAKE_SOURCE_DIR}/include")

