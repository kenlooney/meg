add_test(NAME meg.compiler_help COMMAND meg --help)
set_tests_properties(meg.compiler_help PROPERTIES
  PASS_REGULAR_EXPRESSION "  -h, --help    display this help and exit")

add_executable(meg_byte_buffer_endian_test byte_buffer_endian_test.c)
target_link_libraries(meg_byte_buffer_endian_test PRIVATE meg_core)

add_executable(meg_realmode_realaddress_test realmode_realaddress_test.c)
target_link_libraries(meg_realmode_realaddress_test PRIVATE meg_core)



if(MSVC)
  target_compile_options(meg_byte_buffer_endian_test PRIVATE /W4 /WX /permissive-)
else()
  target_compile_options(meg_byte_buffer_endian_test PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
  target_compile_options(meg_realmode_realaddress_test PRIVATE
    -Wall -Wextra -Wpedantic -Werror)
endif()

add_test(
  NAME meg.byte_buffer.little_endian
  COMMAND meg_byte_buffer_endian_test little)
add_test(
  NAME meg.byte_buffer.big_endian
  COMMAND meg_byte_buffer_endian_test big)

add_test(
  NAME meg.realmode.realaddress
  COMMAND meg_realmode_realaddress_test)
