#include "cfg_symbol.h"
#include <string>

cfg_symbol::cfg_symbol () {
    
}

cfg_symbol::cfg_symbol (cfg_symbol_type symbol_type)
    :type (symbol_type) {

}

cfg_symbol::cfg_symbol (std::string & symbol_name, cfg_symbol_type symbol_type)
	: name (symbol_name), type (symbol_type) {

}

std::string cfg_symbol::get_name()
{

}

cfg_symbol_type cfg_symbol::get_type()
{
    return type;
}

const std::shared_ptr<cfg_production> &cfg_symbol::get_parent_prod() const {
    return parent_prod;
}

void cfg_symbol::set_parent_prod(const std::shared_ptr<cfg_production> &parent_prod) {
    cfg_symbol::parent_prod = parent_prod;
}
