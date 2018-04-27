
#include "synch_production.h"

synch_production::synch_production()
 : production_symbols(), lhs_symbol(SYNCH)
{
    // SYNCH -> SYNCH
    cfg_symbol synch_symbol(SYNCH);
    production_symbols.push_back(synch_symbol);
}

cfg_symbol synch_production::get_lhs_symbol() const
{
    return cfg_symbol();
}

std::vector<cfg_symbol> synch_production::get_symbols() const
{
    return std::vector<cfg_symbol>();
}
