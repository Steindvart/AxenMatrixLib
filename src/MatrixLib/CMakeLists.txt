cmake_minimum_required(VERSION 3.10)

project(MatrixLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Compiler warnings (must be set before `add_subdirectory(...)`)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

option(ENABLE_STRICT_WARNINGS "Enable strict compiler warnings (-Wall, -Wextra, -Werror)" ON)
if(ENABLE_STRICT_WARNINGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

# --- Create library

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES
    ${SOURCE_DIR}/Matrix.cpp
    ${SOURCE_DIR}/Utils.cpp
)

add_library(MatrixLib STATIC ${SOURCES})

target_include_directories(MatrixLib PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/axen/MatrixLib>
)

target_include_directories(MatrixLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/MatrixLib>
)

install(TARGETS MatrixLib
    EXPORT MatrixLibTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION include/MatrixLib
    FILES_MATCHING PATTERN "include/axen/MatrixLib/*.h"
)

install(EXPORT MatrixLibTargets
    FILE MatrixLibTargets.cmake
    NAMESPACE MatrixLib::
    DESTINATION lib/cmake/MatrixLib
)

# --- Enable code coverage

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(MatrixLib PRIVATE -coverage)
    target_link_options(MatrixLib PRIVATE -coverage)
else()
    message(STATUS "Code coverage is disabled. Use -DENABLE_COVERAGE=ON to enable it.")
endif()
