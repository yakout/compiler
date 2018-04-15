cmake_minimum_required(VERSION 3.5)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

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
        lexical_analyzer_generator/nfa_creator.h
        lexical_analyzer/lexical_analyzer.h
        lexical_analyzer_generator/finite_automata/util/util.h
        )

set(SOURCE_FILES main.cpp
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
        lexical_analyzer_generator/nfa_creator.cpp
        lexical_analyzer/lexical_analyzer.cpp
        tests/lexical_analyzer/test.cpp
        lexical_analyzer_generator/finite_automata/util/util.cpp)


add_executable(compiler ${SOURCE_FILES} ${HEADER_FILES})
