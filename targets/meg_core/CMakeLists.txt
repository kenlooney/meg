file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_library(meg_core STATIC ${SOURCES})
target_include_directories(meg_core PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(MSVC)
  target_compile_options(meg_core PRIVATE /W4 /WX /permissive-)
else()
  target_compile_options(meg_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()