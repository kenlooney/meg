add_test(NAME meg.compiler_help COMMAND meg --help)
set_tests_properties(meg.compiler_help PROPERTIES
  PASS_REGULAR_EXPRESSION "  -h, --help    display this help and exit")
  