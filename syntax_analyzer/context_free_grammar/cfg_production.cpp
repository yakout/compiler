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

cfg_symbol cfg_production::get_lhs_symbol () const
{
    return lhs_symbol;
}

std::vector <cfg_symbol> cfg_production::get_symbols () const
{
    return production_symbols;
}

std::string cfg_production::to_string()
{
    if (production_symbols.empty())
        return "";
    std::string name(lhs_symbol.get_name());
    name += " -> ";
    for (cfg_symbol &s : production_symbols)
    {
        if (s.get_name() == EPS)
            name += "\\L ";
        else name += s.get_name() + " ";
    }

    return name.substr(0, name.size() - 1); // remove last space
}

std::string cfg_production::get_rhs_as_string()
{
    if (production_symbols.empty())
        return "";
    std::string name("");
    for (cfg_symbol &s : production_symbols)
    {
        if (s.get_name() == EPS)
            name += "\\L ";
        else name += s.get_name() + " ";
    }

    return name.substr(0, name.size() - 1); // remove last space
}

void cfg_production::pop_first_symbol() 
{
    production_symbols.erase(production_symbols.begin());
}

int cfg_production::find(cfg_symbol symbol)
{
    for (int i = 0; i < production_symbols.size(); i++)
    {
        if (production_symbols[i] == symbol) 
        {
            return i;
        }
    }
    
    return -1;
}
