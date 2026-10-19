cmake_minimum_required(VERSION 3.16)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(lab1_lib
    src/str_ops.cpp
    src/var_10.cpp
    src/buff.cpp
)

target_include_directories(lab1_lib PUBLIC src)

target_compile_options(lab1_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab1_main main.cpp)
target_link_libraries(lab1_main PRIVATE lab1_lib)
target_compile_options(lab1_main PRIVATE -Wall -Wextra -Wpedantic)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab1_tests
    tests/test_variant.cpp
)
target_link_libraries(lab1_tests PRIVATE
    lab1_lib
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(lab1_tests)
