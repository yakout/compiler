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
        intermediate_code_generation/semantic_rules/zeros_ones_counter.h
        intermediate_code_generation/semantic_rules/three_address_code.h
        intermediate_code_generation/semantic_rules/java_bytecode.h)

set (SOURCE_FILES)

add_library (libsemantic SHARED ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(libsemantic PROPERTIES LINKER_LANGUAGE CXX)

add_executable(semantic_main main.cpp)
target_link_libraries(semantic_main libsyntax)
target_link_libraries(semantic_main libsemantic)



# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

# Unit Tests

if (BUILD_UNIT_TEST)
    enable_testing ()
    add_library (catch_semantic INTERFACE)
    target_include_directories (catch_semantic INTERFACE ../tests/lib/)
    add_library (unit_test_catch_semantic STATIC ../tests/catch_main.cpp)
    target_link_libraries (unit_test_catch_semantic catch_semantic)
    target_link_libraries (unit_test_catch_semantic libsemantic)
    target_link_libraries (unit_test_catch_semantic libsyntax)

    macro (do_test test_name)
        add_executable (unit_${test_name}_semantic
            ../tests/semantic_analyzer/unit/${test_name}.cpp)
        target_link_libraries (unit_${test_name}_semantic unit_test_catch_semantic)
        add_test (unit_${test_name}_semantic_analyzer unit_${test_name}_semantic)
    endmacro (do_test)


     do_test(test_1)
 
endif (BUILD_UNIT_TEST)
