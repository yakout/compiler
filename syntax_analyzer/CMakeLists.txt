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
        context_free_grammar/cfg_production.h
        context_free_grammar/cfg_rule.h
        context_free_grammar/cfg_symbol.h
        context_free_grammar/cfg.h
        context_free_grammar/util/first_set.h
        context_free_grammar/util/follow_set.h
        parsing_table.h
        predictive_parser.h
        context_free_grammar/util/follow_set.h
        )

set (SOURCE_FILES
        context_free_grammar/cfg_production.cpp
        context_free_grammar/cfg_rule.cpp
        context_free_grammar/cfg_symbol.cpp
        context_free_grammar/cfg.cpp
        context_free_grammar/util/first_set.cpp
        context_free_grammar/util/follow_set.cpp
        parsing_table.cpp
        predictive_parser.cpp
        )

add_library (libsyntax SHARED ${SOURCE_FILES} ${HEADER_FILES})

add_executable(syntax_main main.cpp)
target_link_libraries(syntax_main libsyntax)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Unit Tests

if (BUILD_UNIT_TEST)
    enable_testing ()
    add_library (catch_syntax INTERFACE)
    target_include_directories (catch_syntax INTERFACE ../tests/lib/)
    add_library (unit_test_catch_syntax STATIC ../tests/catch_main.cpp)
    target_link_libraries (unit_test_catch_syntax catch_syntax)
    target_link_libraries (unit_test_catch_syntax libsyntax)

    macro (do_test test_name)
        add_executable (unit_${test_name}_syntax
            ../tests/syntax_analyzer/unit/${test_name}.cpp)
        target_link_libraries (unit_${test_name}_syntax unit_test_catch_syntax)
        add_test (unit_${test_name}_syntax_analyzer unit_${test_name}_syntax)
    endmacro (do_test)

    do_test (cfg_parser_tests)
    do_test (cfg_tests)
    do_test (ll_1_tests)
    do_test (first_set_tests)
    do_test (follow_set_tests)
    do_test (predictive_parser_tests)
    do_test (parsing_table_tests)
endif (BUILD_UNIT_TEST)
