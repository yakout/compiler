#ifndef COMPILER_CFG_RULE_H
#define COMPILER_CFG_RULE_H

#include <string>
#include <vector>
#include "cfg_production.h"
#include "cfg.h"

class cfg_production;
class cfg;

class cfg_rule
{
private:
    std::string name;
    std::vector<cfg_production> productions;
    std::shared_ptr<cfg> grammer; // parent grammer

public:
    void eliminate_left_recursion();
    void left_factor();

};

#endif //COMPILER_CFG_RULE_H
