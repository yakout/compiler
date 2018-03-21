cmake_minimum_required(VERSION 3.8)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

set(HEADER_FILES 
    lexical_analyzer_generator/finite_automata/finite_automata.h
    lexical_analyzer_generator/finite_automata/state.h
    lexical_analyzer_generator/finite_automata/transition_table.h
    lexical_analyzer_generator/nfa_tools/char_set.h
    lexical_analyzer_generator/nfa_tools/lexical_rules.h
    lexical_analyzer_generator/lexical_analyzer_generator.h
    lexical_analyzer_generator/nfa_creator.h
    lexical_analyzer/lexical_analyzer.h
    lexical_analyzer/token.h)

set(SOURCE_FILES main.cpp 
    lexical_analyzer_generator/finite_automata/finite_automata.cpp
    lexical_analyzer_generator/finite_automata/state.cpp
    lexical_analyzer_generator/lexical_analyzer_generator.cpp
    lexical_analyzer_generator/nfa_creator.cpp)


add_executable(compiler ${SOURCE_FILES} ${HEADER_FILES})


