#ifndef REGEX_PROCESSOR_H
#define REGEX_PROCESSOR_H

#include <memory>
#include <map>
#include <stack>

#include "../finite_automata/nfa.h"
#include "lexical_rules.h"


enum STACK_OPERATOR {
    CONCAT,
    UNION,
    STAR,
    PLUS,
    LEFT_PAREN,
};

/// Operators
#define UNION_SYMBOL '|'
#define STAR_SYMBOL '*'
#define PLUS_SYMBOL '+'
#define LEFT_PAREN_SYMBOL '('
#define RIGHT_PAREN_SYMBOL ')'

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
