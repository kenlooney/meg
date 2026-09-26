file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(meg ${SOURCES})
target_include_directories(meg PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(meg meg_core)

if(MSVC)
  target_compile_options(meg PRIVATE /W4 /WX /permissive-)
else()
  target_compile_options(meg PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Install rules
install(TARGETS meg RUNTIME DESTINATION bin)
install(FILES README.md LICENSE DESTINATION share/doc/meg)