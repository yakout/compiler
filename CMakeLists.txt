cmake_minimum_required (VERSION 3.5)
project (compiler)

set (CMAKE_CXX_STANDARD 11)

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------

# set (CMAKE_CXX_COMPILER g++-7)

#set (GCC_COMPILE_FLAGS "-Wall -Wextra -g")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

option (BUILD_REG_TEST "Determines whether to build regression tests or not" OFF)

# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

add_subdirectory (lexical_analyzer)
add_subdirectory (syntax_analyzer)
add_subdirectory (semantic_analyzer)

add_executable (compiler main.cpp)
target_link_libraries (compiler liblex libsyntax)

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")

# ------------------------------------------------------------------------------
# Code Coverage (not used yet)
# ------------------------------------------------------------------------------

# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# include(CodeCoverage)
# setup_target_for_coverage(cov ${TEST_RUNNER} coverage)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Regression Tests

if (BUILD_REG_TEST)
    enable_testing ()

    #  LEXICAL ANALYZER REGRESION TEST
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

    #  SYNTAX ANALYZER REGRESION TEST (not ll1 grammar)
    add_test (reg_test_0_syntax_analyzer_run compiler --parse
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_0/transition_table.txt
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_0/code.txt
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_0/cfg.bnf)
    # add_test (reg_test_0_syntax_analyzer_compare_debug_stack ${CMAKE_COMMAND} -E compare_files
    #         ${PROJECT_SOURCE_DIR}/build/debug_stack.log
    #         ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_0/debug_stack.log)
    # add_test (reg_test_0_syntax_analyzer_compare_actions_output ${CMAKE_COMMAND} -E compare_files
    #         ${PROJECT_SOURCE_DIR}/build/actions_output.log
    #         ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_0/actions_output.log)

    #  SYNTAX ANALYZER REGRESION TEST (ll1 grammar)
    add_test (reg_test_1_syntax_analyzer_run compiler --parse
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_1/transition_table.txt
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_1/code.txt
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_1/ll1_cfg.bnf)
    add_test (reg_test_1_syntax_analyzer_compare_debug_stack ${CMAKE_COMMAND} -E compare_files
            ${PROJECT_SOURCE_DIR}/build/debug_stack.log
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_1/debug_stack.log)
    add_test (reg_test_1_syntax_analyzer_compare_actions_output ${CMAKE_COMMAND} -E compare_files
            ${PROJECT_SOURCE_DIR}/build/actions_output.log
            ${PROJECT_SOURCE_DIR}/tests/syntax_analyzer/regression/test_1/actions_output.log)

endif (BUILD_REG_TEST)
