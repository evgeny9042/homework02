cmake_minimum_required(VERSION 3.2)

project(ipfilter VERSION 0.0.1)

configure_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/my_version.h)

add_executable(ipfilter main.cpp)

set_target_properties(ipfilter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS ipfilter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT egavrilin90@gmail.com)

include(CPack)