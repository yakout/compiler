#ifndef COMPILER_CFG_SYMBOL_H
#define COMPILER_CFG_SYMBOL_H

#include "cfg_production.h"
#include <string>
#include <memory>

enum cfg_symbol_type
{
    TERMINAL,
    NON_TERMINAL,
    END_MARKER,
    SYNCH
};

class cfg_production;

class cfg_symbol
{
private:
    std::string name;
    std::shared_ptr<cfg_production> prod; // parent
    cfg_symbol_type type;
public:
	cfg_symbol ();
	explicit cfg_symbol (cfg_symbol_type);
    std::string get_name ();
    cfg_symbol_type get_type ();
};

#endif //COMPILER_CFG_SYMBOL_H
