#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "cfg_rule.h"
#include "util/cfg_set.h"

#include <string>
#include <vector>
#include <memory>

class cfg_rule;
class cfg_symbol;
class cfg_set;

class cfg {
private:
    std::vector <std::string> non_terminals; // Vector of symbols badal eletneen dool
    std::vector <std::string> terminals;
    std::vector <cfg_rule> rules;
    std::string start_symbol;

    std::vector<cfg_symbol> cfg_symbols;

public:
    cfg();
    void parse(std::string grammar_file);
    void add_rule();

    std::shared_ptr<cfg_set> get_first_set();
    std::shared_ptr<cfg_set> get_follow_set();
    bool is_ll_1();

    const std::vector<cfg_symbol> &get_cfg_symbols() const;
    void set_cfg_symbols(const std::vector<cfg_symbol> &cfg_symbols);

    /// getters
    std::vector <std::string> get_non_terminals ();
    std::vector <std::string> get_terminals ();
    std::vector <cfg_rule> get_rules ();
    std::string get_start_symbol ();

};


#endif //COMPILER_CFG_H
