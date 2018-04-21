#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "cfg_rule.h"

#include <string>
#include <vector>

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

    /// getters
    std::vector <std::string> get_non_terminals ();
    std::vector <std::string> get_terminals ();
    std::vector <cfg_rule> get_rules ();
    std::string get_start_symbol ();

};


#endif //COMPILER_CFG_H
