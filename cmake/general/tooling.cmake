if (${PROJECT_NAME}_TIDY)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy 
    "-checks=*,-fuchsia-*,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,\
    -llvm-namespace-comment,-google-readability-namespace-comments,-hicpp-no-array-decay,\
    -clang-analyzer-deadcode.DeadStores,-cppcoreguidelines-pro-bounds-pointer-arithmetic,\
    -cppcoreguidelines-pro-type-static-cast-downcast")
endif()

if (${PROJECT_NAME}_IWYU)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)
endif()
