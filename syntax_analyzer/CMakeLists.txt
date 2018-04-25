cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

option (BUILD_UNIT_TEST "Determines whether to build unit tests or not" OFF)

# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

set (HEADER_FILES
        context_free_grammar/cfg_production.h
        context_free_grammar/cfg_rule.h
        context_free_grammar/cfg_symbol.h
        context_free_grammar/cfg.h
        context_free_grammar/parsing_table.h
        context_free_grammar/util/cfg_set.h
        predictive_parser.h)

set (SOURCE_FILES
        context_free_grammar/cfg_production.cpp
        context_free_grammar/cfg_rule.cpp
        context_free_grammar/cfg_symbol.cpp
        context_free_grammar/cfg.cpp
        context_free_grammar/parsing_table.cpp
        context_free_grammar/util/cfg_set.cpp
        predictive_parser.cpp)

add_library (libsyntax SHARED ${SOURCE_FILES} ${HEADER_FILES})

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

    macro (do_test test_num)
        add_executable (unit_test_${test_num}_syntax 
            ../tests/syntax_analyzer/unit/test_${test_num}.cpp)
        target_link_libraries (unit_test_${test_num}_syntax unit_test_catch_syntax)
        add_test (unit_test_${test_num}_syntax_analyzer unit_test_${test_num}_syntax)
    endmacro (do_test)

    do_test (1)
endif (BUILD_UNIT_TEST)