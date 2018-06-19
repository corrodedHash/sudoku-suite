include(ExternalProject)
find_package(Git REQUIRED)

include( "ExternalLLVM" )

ExternalProject_Get_Property(download_llvm_6_0 SOURCE_DIR)

ExternalProject_ADD(
  extlib_msanlibcxx_6_0
  DOWNLOAD_COMMAND ""
  PREFIX ${CMAKE_BINARY_DIR}/externals/msanlibcxx
  SOURCE_DIR ${SOURCE_DIR}
  DEPENDS download_libcxx_6_0 download_libcxxabi_6_0

  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DLLVM_USE_SANITIZER=Memory -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_CXX_COMPILER=clang++
  LOG_CONFIGURE ON

  BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} cxx 
  INSTALL_COMMAND ${CMAKE_MAKE_PROGRAM} install-cxx install-cxxabi
  LOG_BUILD ON
  )

ExternalProject_Get_Property(extlib_msanlibcxx_6_0 INSTALL_DIR)

set_source_files_properties(
  "${INSTALL_DIR}/lib/libc++.so" "${INSTALL_DIR}/lib/libc++abi.so"
  PROPERTIES GENERATED TRUE
  )

add_library(libcxx::msanlibcxx INTERFACE IMPORTED)
add_dependencies(libcxx::msanlibcxx extlib_msanlibcxx_6_0)

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

