cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------

#set (GCC_COMPILE_FLAGS "-Wall -Wextra -g")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

option (BUILD_UNIT_TEST "Determines whether to build unit tests or not" OFF)

# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------


set (HEADER_FILES
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
        lexical_analyzer_generator/finite_automata/util/util.h
        lexical_tokenizer/lexical_tokenizer.h
        lexical_tokenizer/token.h)

set (SOURCE_FILES
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
        lexical_analyzer_generator/finite_automata/util/util.cpp
        lexical_tokenizer/lexical_tokenizer.cpp)

add_library (liblex SHARED ${SOURCE_FILES} ${HEADER_FILES})

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Unit Tests

if (BUILD_UNIT_TEST)
    enable_testing ()
    add_library (catch_lex INTERFACE)
    target_include_directories (catch_lex INTERFACE ../tests/lib/)  
    add_library (unit_test_catch_lexical STATIC ../tests/catch_main.cpp)
    target_link_libraries (unit_test_catch_lexical catch_lex)
    target_link_libraries (unit_test_catch_lexical liblex)

    macro (do_test test_name)
        add_executable (unit_${test_name}_lexical
            ../tests/lexical_analyzer/unit/${test_name}.cpp)
        target_link_libraries (unit_${test_name}_lexical unit_test_catch_lexical)
        add_test (unit_${test_name}_lexical_analyzer unit_${test_name}_lexical)
    endmacro (do_test)

    do_test (test_1)
endif (BUILD_UNIT_TEST)