#include "cfg_rule.h"

cfg_rule::cfg_rule()
        : productions()
{

}

cfg_rule::cfg_rule(std::shared_ptr<cfg> g)
        : productions(), grammar(g)
{

}

void cfg_rule::eliminate_left_recursion()
{

}

void cfg_rule::left_factor()
{

}

std::vector<cfg_production> cfg_rule::get_productions()
{
    return productions;
}


