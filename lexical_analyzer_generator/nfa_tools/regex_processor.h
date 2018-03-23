#ifndef REGEX_PROCESSOR_H
#define REGEX_PROCESSOR_H

#include <memory>
#include <map>
#include <stack>

#include "../finite_automata/nfa.h"
#include "lexical_rules.h"

/// Operators
#define CONCAT '\0'
#define UNION '|'
#define STAR '*'
#define PLUS '+'
#define LEFT_PAREN '('
#define RIGHT_PAREN ')'
/// Range separator
#define RANGE_SEP '-'
/// Parsing characters
#define EPS '\0'
#define SPACE ' '
#define ESC '\\'
#define LAMBDA 'L'

std::shared_ptr <nfa> evaluate_regex (regular_expression regex,
                                      std::map <std::string,
                                      std::shared_ptr<nfa>> &sym_table);

#endif // REGEX_PROCESSOR_H
