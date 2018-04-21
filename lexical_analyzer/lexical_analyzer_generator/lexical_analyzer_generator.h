#ifndef LEXICAL_ANALYZER_GENERATOR_H
#define LEXICAL_ANALYZER_GENERATOR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "nfa_tools/lexical_rules.h"
#include "nfa_tools/regex_processor.h"
#include "finite_automata/nfa.h"
#include "finite_automata/dfa.h"

std::shared_ptr<nfa> build_combined_nfa (std::vector<std::string> rules_file_lines);

std::shared_ptr<nfa> build_regex_nfa (std::string lhs, std::string rhs,
                                      std::map <std::string,
                                      std::shared_ptr<nfa>> &sym_table,
                                      int order);

std::shared_ptr<nfa> build_keywords_nfa (std::string line, int order);

std::shared_ptr<nfa> build_punctations_nfa (std::string line, int order);


class lexical_analyzer_generator
{
    public:
      std::shared_ptr<nfa> get_lexical_analyzer_file(std::string rules_file);
};

#endif // LEXICAL_ANALYZER_GENERATOR_H
