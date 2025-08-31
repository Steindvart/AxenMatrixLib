cmake_minimum_required(VERSION 3.10)

project(MatrixLibTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include(GoogleTest)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(MatrixLibTests ${SOURCES})

target_link_libraries(MatrixLibTests PRIVATE
    MatrixLib
    GTest::gtest_main
)

gtest_discover_tests(MatrixLibTests)

# --- Enable code coverage

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(MatrixLibTests PRIVATE -coverage)
    target_link_options(MatrixLibTests PRIVATE -coverage)
else()
    message(STATUS "Code coverage is disabled. Use -DENABLE_COVERAGE=ON to enable it.")
endif()