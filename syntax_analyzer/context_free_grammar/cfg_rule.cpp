#include "cfg_rule.h"

cfg_rule::cfg_rule () 
            : lhs_symbol (), productions () {
    
}

cfg_rule::cfg_rule (cfg_symbol & symbol
            , std::vector <cfg_production> & prods) 
            : lhs_symbol (symbol), productions (prods) {
    
}

const cfg_symbol & cfg_rule::get_lhs_symbol () const {
    return lhs_symbol;
}

const std::vector <cfg_production> & cfg_rule::get_productions () const {
    return productions;
}