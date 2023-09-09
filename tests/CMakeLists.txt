cmake_minimum_required(VERSION 3.12)

set(TEST_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(TESTED_EXECUTABLE_PATH ${CMAKE_BINARY_DIR}/src/${IP_FILTER_PROJECT_NAME})

configure_file(config.h.in config.h @ONLY)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(TEST_SOURCES test_ip_filter_linux.cpp)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(TEST_SOURCES test_ip_filter_linux.cpp)
#    message(FATAL_ERROR "Unsupported OS - '${CMAKE_SYSTEM_NAME}'")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(FATAL_ERROR "Unsupported OS - '${CMAKE_SYSTEM_NAME}'")
else()
    message(FATAL_ERROR "Unsupported OS - '${CMAKE_SYSTEM_NAME}'")
endif()

find_package(GTest REQUIRED)

enable_testing()

add_executable(tests ${TEST_SOURCES})

set_target_properties(tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(tests PUBLIC
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
