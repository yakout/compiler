cmake_minimum_required (VERSION 3.5)
project (compiler)

set (CMAKE_CXX_STANDARD 11)


# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

add_subdirectory(syntax_analyzer)

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
        lexical_analyzer_generator/finite_automata/util/util.h)

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
        lexical_analyzer_generator/finite_automata/util/util.cpp)

add_library(lexical SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_executable(compiler main.cpp)
target_link_libraries(compiler lexical)



# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------

set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set (MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")


# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

include (CTest)

enable_testing ()

# Regression Tests

add_test (lex_test_0_run compiler --lex -g 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_0/rules.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_0/test_0.txt)

add_test (lex_test_0_compare_token_file ${CMAKE_COMMAND} -E compare_files 
                ${PROJECT_SOURCE_DIR}/build/token-file.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_0/token-file.txt)
                
add_test (lex_test_0_compare_symbol_table ${CMAKE_COMMAND} -E compare_files 
                ${PROJECT_SOURCE_DIR}/build/symbol-table.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_0/symbol-table.txt)

add_test (lex_test_0_compare_log ${CMAKE_COMMAND} -E compare_files 
                ${PROJECT_SOURCE_DIR}/build/compiler.log 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_0/compiler.log)

macro (do_test test_num)
        add_test (lex_test_${test_num}_run compiler --lex 
                ${PROJECT_SOURCE_DIR}/build/transition_table.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_${test_num}/test_${test_num}.txt)

        add_test (lex_test_${test_num}_compare_token_file ${CMAKE_COMMAND} 
                -E compare_files ${PROJECT_SOURCE_DIR}/build/token-file.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_${test_num}/token-file.txt)

        add_test (lex_test_${test_num}_compare_symbol_table ${CMAKE_COMMAND} 
                -E compare_files ${PROJECT_SOURCE_DIR}/build/symbol-table.txt 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_${test_num}/symbol-table.txt)

        add_test (lex_test_${test_num}_compare_log ${CMAKE_COMMAND} 
                -E compare_files ${PROJECT_SOURCE_DIR}/build/compiler.log 
                ${PROJECT_SOURCE_DIR}/tests/lexical_analyzer/test_${test_num}/compiler.log)
endmacro (do_test)

 do_test(1)
 do_test(2)
 do_test(3)
 do_test(4)
 do_test(5)
 do_test(6)


# Unit Tests

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${PROJECT_SOURCE_DIR}/tests/lib/)

add_library(test_catch STATIC tests/test.cpp)
target_link_libraries(test_catch Catch)

macro(do_test test_num module)
    add_executable(test_${test_num}_${module} ${PROJECT_SOURCE_DIR}/tests/${module}/test_${test_num}.cpp)
    target_link_libraries(test_${test_num}_${module} test_catch)
    target_link_libraries(test_${test_num}_${module} ${module})

    add_test(test_${test_num}_${module} test_${test_num}_${module})
endmacro(do_test)

do_test(1 lexical)
do_test(1 syntax)
