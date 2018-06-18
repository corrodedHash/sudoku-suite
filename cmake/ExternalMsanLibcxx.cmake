include(ExternalProject)
find_package(Git REQUIRED)

set(MSANLIBCXX_EXTERNAL_ROOT ${CMAKE_BINARY_DIR}/externals/msanlibcxx)
set(MSANLIBCXX_EXTERNAL_REPO "https://github.com/llvm-mirror/llvm.git")
set(INSTALL_DIR "${MSANLIBCXX_EXTERNAL_ROOT}")

add_custom_command (
  OUTPUT "${INSTALL_DIR}/llvm/"
  COMMAND git clone --depth 1 -b release_60 --single-branch "https://github.com/llvm-mirror/llvm.git" "${INSTALL_DIR}/llvm" || true
  WORKING_DIRECTORY  ${INSTALL_DIR}
  COMMENT "Cloning llvm"
  )

add_custom_command (
  OUTPUT "${INSTALL_DIR}/llvm/projects/libcxx/"
  COMMAND git clone --depth 1 -b release_60 --single-branch "https://github.com/llvm-mirror/libcxx.git" "${INSTALL_DIR}/llvm/projects/libcxx" || true
  DEPENDS "${INSTALL_DIR}/llvm/"
  COMMENT "Cloning libcxx"
  )

add_custom_command (
  OUTPUT "${INSTALL_DIR}/llvm/projects/libcxxabi"
  COMMAND git clone --depth 1 -b release_60 --single-branch "https://github.com/llvm-mirror/libcxxabi.git" "${INSTALL_DIR}/llvm/projects/libcxxabi" || true
  DEPENDS "${INSTALL_DIR}/llvm/"
  COMMENT "Cloning libcxxabi"
  )

add_custom_command(
  OUTPUT "${INSTALL_DIR}/lib/libc++.so" "${INSTALL_DIR}/lib/libc++abi.so"
  COMMAND mkdir -p llvm/build
  COMMAND cd llvm/build
  COMMAND cmake -G ${CMAKE_GENERATOR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DLLVM_USE_SANITIZER=Memory -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -DCMAKE_CXX_COMPILER=clang++ ..
  COMMAND ${CMAKE_MAKE_PROGRAM} cxx install-cxx install-cxxabi
  WORKING_DIRECTORY ${MSANLIBCXX_EXTERNAL_ROOT}
  DEPENDS
  "${INSTALL_DIR}/llvm/projects/libcxx/"
  "${INSTALL_DIR}/llvm/projects/libcxxabi"
  COMMENT "Building MSAN libcxx"
  )


add_custom_target(extlib_msanlibcxx SOURCES "${INSTALL_DIR}/lib/libc++.so" "${INSTALL_DIR}/lib/libc++abi.so")

message(STATUS
  "${INSTALL_DIR}/lib/libc++.so" )
add_library(libcxx::msanlibcxx INTERFACE IMPORTED)
add_dependencies(libcxx::msanlibcxx extlib_msanlibcxx)
target_link_libraries(libcxx::msanlibcxx INTERFACE
  "${INSTALL_DIR}/lib/libc++.so"
  "${INSTALL_DIR}/lib/libc++abi.so"
  )
target_include_directories(libcxx::msanlibcxx SYSTEM INTERFACE
  "${INSTALL_DIR}/include"
  "${INSTALL_DIR}/include/c++/v1"
  )

target_link_libraries(libcxx::msanlibcxx INTERFACE "-stdlib=libc++")
target_compile_options(libcxx::msanlibcxx INTERFACE "-stdlib=libc++")

