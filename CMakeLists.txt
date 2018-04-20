cmake_minimum_required(VERSION 3.5)
project(compiler)

set(CMAKE_CXX_STANDARD 11)


# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

set(HEADER_FILES
        lexical_analyzer_generator/finite_automata/finite_automata.h
        lexical_analyzer_generator/finite_automata/state.h
        lexical_analyzer_generator/finite_automata/nfa.h
        lexical_analyzer_generator/finite_automata/dfa.h
        lexical_analyzer_generator/finite_automata/nfa_state.h
        lexical_analyzer_generator/finite_automata/dfa_state.h
        lexical_analyzer_generator/nfa_tools/char_set.h
        lexical_analyzer_generator/nfa_tools/char_range.h
        lexical_analyzer_generator/nfa_tools/lexical_rules.h
        lexical_analyzer_generator/nfa_tools/regex_processor.h
        lexical_analyzer_generator/lexical_analyzer_generator.h
        lexical_analyzer/lexical_analyzer.h
        lexical_analyzer_generator/finite_automata/util/util.h
        )

set(SOURCE_FILES
        lexical_analyzer_generator/finite_automata/finite_automata.cpp
        lexical_analyzer_generator/finite_automata/state.cpp
        lexical_analyzer_generator/finite_automata/nfa_state.cpp
        lexical_analyzer_generator/finite_automata/dfa_state.cpp
        lexical_analyzer_generator/finite_automata/nfa.cpp
        lexical_analyzer_generator/finite_automata/dfa.cpp
        lexical_analyzer_generator/nfa_tools/char_set.cpp
        lexical_analyzer_generator/nfa_tools/char_range.cpp
        lexical_analyzer_generator/nfa_tools/lexical_rules.cpp
        lexical_analyzer_generator/nfa_tools/regex_processor.cpp
        lexical_analyzer_generator/lexical_analyzer_generator.cpp
        lexical_analyzer/lexical_analyzer.cpp
        lexical_analyzer_generator/finite_automata/util/util.cpp
        )

add_library(lexical STATIC ${SOURCE_FILES})
add_executable(compiler main.cpp ${SOURCE_FILES} ${HEADER_FILES})


# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

include (CTest)

enable_testing()

# Regression Tests

add_test( test_0_run compiler --lex -g ${PROJECT_SOURCE_DIR}/tests/rules.txt ${PROJECT_SOURCE_DIR}/tests/test_program.txt)
add_test( test_0 ${CMAKE_COMMAND} -E compare_files ${PROJECT_SOURCE_DIR}/build/token-file.txt ${PROJECT_SOURCE_DIR}/tests/token-file.txt)

macro(do_test test_num)
        add_test( test_${test_num}_run compiler --lex ${PROJECT_SOURCE_DIR}/build/transition_table.txt ${PROJECT_SOURCE_DIR}/tests/test_${test_num}/test_${test_num}.txt)

        add_test( test_${test_num}_compare_token_file ${CMAKE_COMMAND} -E compare_files ${PROJECT_SOURCE_DIR}/build/token-file.txt ${PROJECT_SOURCE_DIR}/tests/test_${test_num}/token-file.txt)

        add_test( test_${test_num}_compare_symbol_table ${CMAKE_COMMAND} -E compare_files ${PROJECT_SOURCE_DIR}/build/symbol-table.txt ${PROJECT_SOURCE_DIR}/tests/test_${test_num}/symbol-table.txt)

        add_test( test_${test_num}_compare_log ${CMAKE_COMMAND} -E compare_files ${PROJECT_SOURCE_DIR}/build/compiler.log ${PROJECT_SOURCE_DIR}/tests/test_${test_num}/compiler.log)
endmacro(do_test)

 do_test(1)
 do_test(2)
 do_test(3)
 do_test(4)
 do_test(5)

# Unit Tests

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${PROJECT_SOURCE_DIR}/tests/lib/)

add_library(test_catch STATIC ${PROJECT_SOURCE_DIR}/tests/lexical/test.cpp)
target_link_libraries(test_catch Catch)

macro(do_test test_num)
    add_executable(test_${test_num} ${PROJECT_SOURCE_DIR}/tests/lexical/test_${test_num}.cpp)
    target_link_libraries(test_${test_num} test_catch)
    target_link_libraries(test_${test_num} lexical)

    add_test(test_${test_num} test_${test_num})
endmacro(do_test)

do_test(1)
