
#include "parsing_table.h"

parsing_table::parsing_table(cfg grammar, first_follow_sets first_follow) {
    this->grammar = grammar;
    this->first_follow = first_follow;
}

parsing_table::parsing_table() {}


void parsing_table::build() {
    
}
