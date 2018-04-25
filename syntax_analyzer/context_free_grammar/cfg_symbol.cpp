#include <string>
#include "cfg_symbol.h"

cfg_symbol::cfg_symbol ()
{

}

cfg_symbol::cfg_symbol (cfg_symbol_type t)
	: type(t), name("$")
{
	prod = nullptr;
}

std::string cfg_symbol::get_name()
{

}

cfg_symbol_type cfg_symbol::get_type()
{
    return type;
}
