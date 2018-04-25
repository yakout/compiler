#include "cfg_production.h"

cfg_production::cfg_production()
        : prod()
{

}

cfg_production::cfg_production(std::shared_ptr<cfg_rule> r)
        : rule(r)
{

}

std::string cfg_production::get_name()
{
    return name;
}

std::vector<cfg_symbol> cfg_production::get_symbols ()
{
    return prod;
}


