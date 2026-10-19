cmake_minimum_required(VERSION 3.16)
project(lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(polynomial src/polynomial.cpp)
target_include_directories(polynomial PUBLIC "src")
target_compile_options(polynomial PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab_2 main.cpp)
target_link_libraries(lab_2 PRIVATE polynomial)
target_compile_options(lab_2 PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

find_package(GTest CONFIG QUIET)
if(NOT GTest_FOUND)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(polynomial_tests tests/test_polynomial.cpp)
target_link_libraries(polynomial_tests PRIVATE polynomial GTest::gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(polynomial_tests)
