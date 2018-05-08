#include "cfg_symbol.h"

cfg_symbol::cfg_symbol ()
	: name (), type ()
{

}

cfg_symbol::cfg_symbol (cfg_symbol_type symbol_type)
    : name (), type (symbol_type) 
{

}

cfg_symbol::cfg_symbol (const std::string & symbol_name, cfg_symbol_type symbol_type)
	: name (symbol_name), type (symbol_type) 
{

}

std::string cfg_symbol::get_name() const 
{
    return name;
}

cfg_symbol_type cfg_symbol::get_type() const 
{
    return type;
}

void cfg_symbol::set_action(std::function<void(std::vector<cfg_symbol> &)> action)
{
    cfg_symbol::action = action;
}

void cfg_symbol::add_attribute(std::string name, std::string value) 
{
	attributes[name] = value;
}

std::string cfg_symbol::get_attribute(std::string name)
{
	return attributes[name];
}

const std::function<void(std::vector<cfg_symbol> &)> &cfg_symbol::get_action() const
{
    return action;
}
