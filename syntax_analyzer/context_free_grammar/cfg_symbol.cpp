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
	attributes[name].push_back(value);
}

void cfg_symbol::add_attribute(std::string name, std::vector<std::string> values)
{
    for (auto value : values)
    {
        attributes[name].push_back(value);
    }
}

void cfg_symbol::add_inherited_attribute(std::string name, std::string value) {
    inherited_attributes[name].push_back(value);
}

std::vector<std::string> cfg_symbol::get_attribute(std::string name)
{
	return attributes[name];
}

const std::function<void(std::vector<cfg_symbol> &)> &cfg_symbol::get_action() const
{
    return action;
}

bool cfg_symbol::is_term_or_non_term() {
    return cfg_symbol::type == TERMINAL || cfg_symbol::type == NON_TERMINAL;
}

std::vector<std::string> cfg_symbol::get_inherited_attribute(std::string name) {
    return inherited_attributes[name];
}

bool cfg_symbol::has_inherited_attribute() {
    return !inherited_attributes.empty();
}

std::map<std::string, std::vector<std::string>> cfg_symbol::get_inherited_attributes() {
    return inherited_attributes;
}

void cfg_symbol::set_inherited_attributes(std::map<std::string, std::vector<std::string>> inh_attr) {
    inherited_attributes = inh_attr;
}
