cmake_minimum_required (VERSION 3.5)
project (compiler)

set (CMAKE_CXX_STANDARD 11)

option (BUILD_REG_TEST "Determines whether to build regression tests or not" OFF)

# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

add_subdirectory (lexical_analyzer)
add_subdirectory (syntax_analyzer)

include_directories(lexical_analyzer)
include_directories(syntax_analyzer)
include_directories(tests/lib)

add_executable(compiler main.cpp)
target_link_libraries(compiler liblex libsyntax)

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Regression Tests

if (BUILD_REG_TEST)
    enable_testing ()
    add_test (reg_test_0_lexical_analyzer_run compiler --lex -g 
        ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_0/rules.txt 
        ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_0/test_0.txt)

    add_test (reg_test_0_lexical_analyzer_compare_token_file ${CMAKE_COMMAND} -E compare_files 
        ${PROJECT_SOURCE_DIR}/build/token-file.txt 
        ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_0/token-file.txt)

    add_test (reg_test_0_lexical_analyzer_compare_symbol_table ${CMAKE_COMMAND} -E compare_files 
        ${PROJECT_SOURCE_DIR}/build/symbol-table.txt 
        ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_0/symbol-table.txt)

    add_test (reg_test_0_lexical_analyzer_compare_log ${CMAKE_COMMAND} -E compare_files 
        ${PROJECT_SOURCE_DIR}/build/compiler.log 
        ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_0/compiler.log)

    macro (do_test test_num)
        add_test (reg_test_${test_num}_lexical_analyzer_run compiler --lex 
            ${PROJECT_SOURCE_DIR}/build/transition_table.txt 
            ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_${test_num}/test_${test_num}.txt)

        add_test (reg_test_${test_num}_lexical_analyzer_compare_token_file ${CMAKE_COMMAND} 
            -E compare_files ${PROJECT_SOURCE_DIR}/build/token-file.txt 
            ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_${test_num}/token-file.txt)

        add_test (reg_test_${test_num}_lexical_analyzer_compare_symbol_table ${CMAKE_COMMAND} 
            -E compare_files ${PROJECT_SOURCE_DIR}/build/symbol-table.txt 
            ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_${test_num}/symbol-table.txt)

        add_test (reg_test_${test_num}_lexical_analyzer_compare_log ${CMAKE_COMMAND} 
            -E compare_files ${PROJECT_SOURCE_DIR}/build/compiler.log 
            ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/regression/test_${test_num}/compiler.log)
    endmacro (do_test)

    do_test (1)
    do_test (2)
    do_test (3)
    do_test (4)
    do_test (5)
    do_test (6)
endif (BUILD_REG_TEST)
