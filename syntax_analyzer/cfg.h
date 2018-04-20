#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include <string>
#include <vector>
#include "cfg_rule.h"

class cfg_rule;

class cfg {
private:
    std::vector <std::string> non_terminals;
    std::vector <std::string> terminals;
    std::vector <cfg_rule> rules;
    std::string start_symbol;

public:
    cfg();
    void parse(std::string grammer_file);
    void add_rule();
};


#endif //COMPILER_CFG_H
