#include "cfg_production.h"

cfg_production::cfg_production () 
            : lhs_symbol (), production_symbols () {   
}

cfg_production::cfg_production (cfg_symbol & symbol
            , std::vector <cfg_symbol> & symbols) 
            : lhs_symbol (symbol), production_symbols (symbols) {   
}

cfg_symbol cfg_production::get_lhs_symbol () {
    return lhs_symbol;
}

std::vector <cfg_symbol> cfg_production::get_symbols () {
    return production_symbols;
}