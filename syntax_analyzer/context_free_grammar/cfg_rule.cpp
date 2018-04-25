#include "cfg_rule.h"

cfg_rule::cfg_rule () 
            : lhs_symbol (), productions () {
    
}

cfg_rule::cfg_rule (cfg_symbol & symbol
            , std::vector <cfg_production> & prods) 
            : lhs_symbol (symbol), productions (prods) {
    
}

std::vector <cfg_production> cfg_rule::get_productions () {
    return productions;
}