#include "cfg.h"


cfg::cfg()
 : non_terminals (), terminals (), rules ()
{

}

void cfg::parse(std::string grammer_file)
{

}

void cfg::add_rule()
{

}

std::vector <std::string> cfg::get_non_terminals ()
{
    return this->non_terminals;
}

std::vector <std::string> cfg::get_terminals ()
{
    return this->terminals;
}

std::vector <cfg_rule> cfg::get_rules ()
{
    return this->rules;
}

std::string cfg::get_start_symbol ()
{
    return this->start_symbol;
}
