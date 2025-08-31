cmake_minimum_required(VERSION 3.21)

# --- General project settings

project(Matrix VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing() # Must be be set before `add_subdirectory(...)`

# --- Include subprojects

add_subdirectory(src/MatrixLib)
add_subdirectory(src/MatrixLibTests)

# --- Valgrind memory testing

find_program(VALGRIND valgrind)
if(VALGRIND)
    set(MEMORYCHECK_COMMAND ${VALGRIND})
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose")
    set(MEMORYCHECK_SUPPRESSIONS_FILE ${CMAKE_SOURCE_DIR}/valgrind.supp)

    add_custom_target(run_valgrind_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR} -T memcheck --output-on-failure --output-log ${CMAKE_BINARY_DIR}/valgrind-report.txt
        COMMENT "Running tests with valgrind memory check"
        DEPENDS MatrixLibTests
    )
    set_target_properties(run_valgrind_tests PROPERTIES FOLDER "Testing")
else()
    message(WARNING "valgrind not found. Memory checks will be skipped.")
endif()

include(CTest) # Must go after `enable_testing()` and Valgrind memory checks target

# --- Custom targets for clang-format

file(GLOB_RECURSE FORMAT_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_custom_target(clang_check
    COMMAND clang-format -n ${FORMAT_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running clang-format check..."
)
set_target_properties(clang_check PROPERTIES FOLDER "Code Quality")

add_custom_target(clang_format
    COMMAND clang-format -i ${FORMAT_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Applying clang-format..."
)
set_target_properties(clang_format PROPERTIES FOLDER "Code Quality")

# --- clangd support - Make compile_commands.json in the root of build directory

if (CMAKE_EXPORT_COMPILE_COMMANDS)
    # Create symlink to compile_commands.json for IDE to pick it up
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_BINARY_DIR}/../compile_commands.json
    )
endif()

# --- Generate coverage if enabled

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    else()
        message(WARNING "Code coverage is only supported with GCC")
    endif()
endif()

# --- Collect coverage and generate HTML report

if(ENABLE_COVERAGE)
    find_program(LCOV_COMMAND lcov)
    find_program(GENHTML_COMMAND genhtml)
    if(NOT LCOV_COMMAND OR NOT GENHTML_COMMAND)
        message(WARNING "lcov or genhtml not found. Coverage report generation will be skipped.")
    else()
        # Run tests for coverage
        add_custom_target(run_tests_for_coverage
            COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR} --output-on-failure
            COMMENT "Running tests for code coverage"
            DEPENDS MatrixLibTests
        )
        set_target_properties(run_tests_for_coverage PROPERTIES FOLDER "Testing")

        # Generate coverage report
        add_custom_target(coverage
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage
            COMMAND ${LCOV_COMMAND} --capture --directory ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR} --output-file ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage/coverage.info --ignore-errors mismatch
            COMMAND ${LCOV_COMMAND} --remove ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage/coverage.info '/usr/*' --output-file ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage/coverage_filtered.info
            COMMAND ${GENHTML_COMMAND} -o ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage/coverage_filtered.info
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report generated in ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}/coverage/index.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_CFG_INTDIR}
            COMMENT "Generating code coverage report"
            DEPENDS run_tests_for_coverage
        )
        set_target_properties(coverage PROPERTIES FOLDER "Testing")
    endif()
endif()
