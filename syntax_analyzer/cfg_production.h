#ifndef COMPILER_CFG_PRODUCTION_H
#define COMPILER_CFG_PRODUCTION_H

#include <vector>
#include "cfg_symbol.h"
#include "cfg_rule.h"

class cfg_rule;
class cfg_symbol;

class cfg_production
{
private:
    std::string name;
    std::vector<cfg_symbol> prod;
    std::shared_ptr<cfg_rule> rule; // parent rule
public:
    std::string get_name();
};

#endif //COMPILER_CFG_PRODUCTION_H
