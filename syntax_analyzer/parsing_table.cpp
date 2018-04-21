#include "parsing_table.h"

parsing_table::parsing_table(cfg grammar, first_follow_sets first_follow) {
    this->grammar = grammar;
    this->first_follow = first_follow;
}

parsing_table::parsing_table() {}


void parsing_table::build() {
    /*for (size_t i = 0; i < grammar.rules.size(); i++)
    {
        first first_set = first_follow.get_first (grammar.rules[i]);
        follow folow_set = first_follow.get_follow (grammar.rules[i])
    }*/
}
