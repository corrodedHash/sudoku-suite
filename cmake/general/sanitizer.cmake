if (NOT MSVC)
  set(SANITIZER_LIST "")
  if(${${PROJECT_NAME}_SANITIZER_ADDRESS})
    list(APPEND SANITIZER_LIST "address")
    target_compile_options(GeneralConfig INTERFACE
      "-fsanitize-address-use-after-scope"
      "-fno-optimize-sibling-calls")
    target_link_options(GeneralConfig INTERFACE
      "-fsanitize-address-use-after-scope"
      "-fno-optimize-sibling-calls")
  endif()

  if(${${PROJECT_NAME}_SANITIZER_UB})
    list(APPEND SANITIZER_LIST "undefined")
  endif()

  if(${${PROJECT_NAME}_SANITIZER_MEMORY})
    include("external/MsanLibcxx")
    target_link_libraries(GeneralConfig INTERFACE libcxx::msanlibcxx)

    list(APPEND SANITIZER_LIST "memory")
    target_compile_options(GeneralConfig INTERFACE
      "-fsanitize-memory-track-origins")
    target_link_options(GeneralConfig INTERFACE
      "-fsanitize-memory-track-origins")
  endif()

  if (${${PROJECT_NAME}_SANITIZER_CFI})
    # Segfaults with 'illegal hardware instruction'
    list(APPEND SANITIZER_LIST "cfi")
    target_compile_options(GeneralConfig INTERFACE
      "-fvisibility=hidden")
  endif()

  if (${PROJECT_NAME}_FUZZER)
    list(APPEND SANITIZER_LIST "fuzzer-no-link")
  endif()

  add_library(SanitizerConfig INTERFACE)

  if ( SANITIZER_LIST )
    string(REPLACE ";" "," SANITIZER_STRING "${SANITIZER_LIST}" )
    target_compile_options(SanitizerConfig INTERFACE
      "-fsanitize=${SANITIZER_STRING}")
    target_link_options(SanitizerConfig INTERFACE
      "-fsanitize=${SANITIZER_STRING}")
  endif()

  add_library(FuzzerSanitizerConfig INTERFACE)
  target_link_libraries(FuzzerSanitizerConfig INTERFACE GeneralConfig)

  list(REMOVE_ITEM SANITIZER_LIST "fuzzer-no-link")
  list(APPEND SANITIZER_LIST "fuzzer")
  string(REPLACE ";" "," SANITIZER_STRING "${SANITIZER_LIST}" )
  target_compile_options(FuzzerSanitizerConfig INTERFACE
    "-fsanitize=${SANITIZER_STRING},fuzzer")
  target_link_options(FuzzerSanitizerConfig INTERFACE
    "-fsanitize=${SANITIZER_STRING},fuzzer")
endif()
