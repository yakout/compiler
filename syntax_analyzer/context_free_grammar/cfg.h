#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "cfg_rule.h"
#include "util/cfg_set.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

#define EPS "\L"

class cfg {
private:
    std::vector <cfg_symbol> non_terminals;
    std::vector <cfg_symbol> terminals;
    std::vector <cfg_rule> rules;
    cfg_symbol start_symbol;
    std::vector <cfg_symbol> cfg_symbols;
    std::map <std::string, cfg_rule> grammar;

public:
    cfg ();
    explicit cfg (std::string);
    void parse (std::string);
    void add_rule ();

    std::shared_ptr <cfg_set> get_first_set ();
    std::shared_ptr <cfg_set> get_follow_set ();
    bool is_ll_1 ();

    const std::vector<cfg_symbol> &get_cfg_symbols () const;
    void set_cfg_symbols (const std::vector<cfg_symbol> &cfg_symbols);

    /** Getters **/
    std::vector <cfg_symbol> get_non_terminals ();
    std::vector <cfg_symbol> get_terminals ();
    std::vector <cfg_rule> get_rules ();
    cfg_symbol get_start_symbol ();
};

#endif //COMPILER_CFG_H
