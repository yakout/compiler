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

std::vector <cfg_production> & cfg_rule::get_productions ()
{
    return productions;
}

void cfg_rule::empty_productions ()
{
    productions.clear();
}

void cfg_rule::set_productions (std::vector <cfg_production>& new_productions)
{
    productions = new_productions;
}

std::string cfg_rule::to_string() {
    std::string s = "";
    s += lhs_symbol.get_name() + " -> ";
    s += productions[0].get_rhs_as_string();

    for (int i = 1; i < productions.size(); i++) {
        s += " | ";
        s += productions[i].get_rhs_as_string();
    }

    return s;
}

void cfg_rule::add_productions (std::vector <cfg_production> & new_productions) {
    productions.insert(productions.end(), new_productions.begin(), new_productions.end());
}

