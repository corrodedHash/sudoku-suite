add_executable(fuzzer)
target_link_libraries(fuzzer PRIVATE GeneralConfig FuzzerSanitizerConfig)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/corpus)

add_custom_target(fuzz ./fuzzer corpus -print_final_stats=1 -print_pcs=1 -timeout=5 DEPENDS fuzzer USES_TERMINAL)

add_custom_command(OUTPUT default.profdata
  COMMAND llvm-profdata merge -sparse default.profraw -o default.profdata
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/default.profraw)

add_custom_target(fuzz_cov llvm-cov show fuzzer -instr-profile=default.profdata -format=html > default.html
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/default.profdata)
