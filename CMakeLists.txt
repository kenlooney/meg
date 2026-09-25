cmake_minimum_required(VERSION 3.20)
project(HybridChapter01 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")
add_executable(meg ${SOURCES})
if(MSVC)
  target_compile_options(meg PRIVATE /W4 /WX /permissive-)
else()
  target_compile_options(meg PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Install rules
install(TARGETS meg RUNTIME DESTINATION bin)
install(FILES README.md LICENSE DESTINATION share/doc/meg)

include(CTest)

if(BUILD_TESTING)
 add_subdirectory(tests)
endif()

# CPack configuration
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Kenneth Looney")
set(CPACK_PACKAGE_CONTACT "ken.looney05@gmail.com")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME
    "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)
