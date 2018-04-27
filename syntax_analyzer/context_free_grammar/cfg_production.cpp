#include "cfg_production.h"
#include "cfg.h"

cfg_production::cfg_production () 
            : lhs_symbol (), production_symbols ()
{

}

cfg_production::cfg_production (cfg_symbol & symbol
            , std::vector <cfg_symbol> & symbols) 
            : lhs_symbol (symbol), production_symbols (symbols)
{
}

void cfg_production::set_lhs_symbol (cfg_symbol & lhs_symbol) {
    cfg_production::lhs_symbol = lhs_symbol;
}
void cfg_production::add_symbol (cfg_symbol & sym) {
    production_symbols.push_back (sym);
}

cfg_symbol cfg_production::get_lhs_symbol ()
{
    return lhs_symbol;
}

std::vector <cfg_symbol> cfg_production::get_symbols ()
{
    return production_symbols;
}

std::string cfg_production::get_name()
{
    if (production_symbols.empty())
        return "";
    std::string name(lhs_symbol.get_name());
    name += " -> ";
    for (cfg_symbol &s : production_symbols)
    {
        if (s.get_name() == EPS)
            name += "\\E";
        else name += s.get_name();
    }

    return name;
}
