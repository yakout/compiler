#ifndef COMPILER_CFG_PRODUCTION_H
#define COMPILER_CFG_PRODUCTION_H

#include "cfg_symbol.h"
#include "cfg_rule.h"
#include <memory>
#include <vector>

class cfg_rule;
class cfg_symbol;

class cfg_production
{
private:
    std::string name;
    std::vector<cfg_symbol> prod;
    std::shared_ptr<cfg_rule> rule; // parent rule
public:
    cfg_production();
    explicit cfg_production(std::shared_ptr<cfg_rule>);

    /// getters
    std::string get_name();
    std::vector<cfg_symbol> get_symbols();
};

#endif //COMPILER_CFG_PRODUCTION_H
