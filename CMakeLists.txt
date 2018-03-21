cmake_minimum_required(VERSION 3.9)
project(java_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(java_compiler
        main.cpp
        lexical_analyzer_generator/lexical_analyzer_generator.cpp
        lexical_analyzer_generator/finite_automata/finite_automata.cpp
        lexical_analyzer_generator/finite_automata/state.cpp
        lexical_analyzer_generator/nfa_tools/char_set.cpp
        lexical_analyzer_generator/nfa_creator.cpp
        )
