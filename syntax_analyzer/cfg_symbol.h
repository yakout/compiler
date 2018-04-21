#ifndef COMPILER_CFG_SYMBOL_H
#define COMPILER_CFG_SYMBOL_H

#include "cfg_production.h"
#include <string>
#include <memory>

enum cfg_symbol_type
{
    TERMINAL,
    NON_TERMINAL,
    END_MARKER
};

class cfg_production;

class cfg_symbol
{
    std::string name;
    std::shared_ptr<cfg_production> prod;
    cfg_symbol_type type;
public:
    std::string get_name();
    cfg_symbol_type get_type();
};

#endif //COMPILER_CFG_SYMBOL_H
