cmake_minimum_required(VERSION 3.2)

project(ip_filter  VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

if(FORTSDK)
	SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files (x86)/Fort SDK/include/boost")
	SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files (x86)/Fort SDK/lib/win32-msvc2015/boost")
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter  main.cpp lib.cpp)
add_executable(test_filter test.cpp lib.cpp)

set_target_properties(ip_filter test_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
set_target_properties(test_filter PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(test_filter
    ${Boost_LIBRARIES}
)

install(TARGETS ip_filter  RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT egavrilin90@gmail.com)

include(CPack)

enable_testing()

add_test(test_filter test_filter)