include( "external/Catch2" )

add_executable(testing)

target_link_libraries(testing PRIVATE GeneralConfig SanitizerConfig)
target_link_libraries(testing PRIVATE Catch2::Catch2)

add_custom_target(test ./testing)

add_custom_target(test_cov ./testing
  COMMAND llvm-profdata merge -o testing.profdata default.profraw
  COMMAND llvm-cov report --use-color --instr-profile testing.profdata ./testing
  COMMAND rm -i -rf testing_cov_report
  COMMAND llvm-cov show --use-color --format=html -o testing_cov_report --instr-profile testing.profdata ./testing)
