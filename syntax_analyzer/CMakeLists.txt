cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

# ------------------------------------------------------------------------------
# Build
# ------------------------------------------------------------------------------

set (HEADER_FILES
        cfg_production.h
        cfg_rule.h
        cfg_symbol.h
        cfg.h
        parsing_table.h
        predictive_parser.h)

set (SOURCE_FILES
        cfg_production.cpp
        cfg_rule.cpp
        cfg_symbol.cpp
        cfg.cpp
        parsing_table.cpp
        predictive_parser.cpp)

add_library (libsyntax SHARED ${SOURCE_FILES} ${HEADER_FILES})

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Unit Tests

add_library (catch_syntax INTERFACE)
target_include_directories (catch_syntax INTERFACE ../tests/lib/)
add_library (unit_test_catch_syntax STATIC ../tests/catch_main.cpp)
target_link_libraries (unit_test_catch_syntax catch_syntax)

macro (do_test test_num)
    add_executable (unit_test_${test_num}_syntax 
        ../tests/syntax_analyzer/unit/test_${test_num}.cpp)
    target_link_libraries (unit_test_${test_num}_syntax unit_test_catch_syntax)
    target_link_libraries (unit_test_${test_num}_syntax libsyntax)
    
    add_test (unit_test_${test_num}_syntax_analyzer unit_test_${test_num}_syntax)
endmacro (do_test)

do_test (1)