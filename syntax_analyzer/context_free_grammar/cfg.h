#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "cfg_rule.h"
#include "util/cfg_set.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <unordered_map>

#define EPS "\\L"

class cfg {
private:
    std::vector <cfg_symbol> non_terminals;
    std::vector <cfg_symbol> terminals;
    std::vector <cfg_rule> rules;
    cfg_symbol start_symbol;
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> cfg_symbols;
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> cfg_symbol_productions;

    void process_first_set(int prod_symbol_index, std::shared_ptr<cfg_set> first_set,
                           cfg_production *prod);
    void process_follow_set(cfg_symbol non_terminal, std::shared_ptr<cfg_set> follow_set);

public:
    cfg ();
    explicit cfg (std::string);

    const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &
    get_cfg_symbol_productions() const;

    void set_cfg_symbol_productions(
            const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &cfg_symbol_productions);
    void set_non_terminals(const std::vector<cfg_symbol> &non_terminals);
    const std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> &get_grammar() const;
    void
    set_grammar(const std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> &grammar);
    void parse (std::string);
    void add_rule ();
    std::shared_ptr <cfg_set> get_first_set ();
    std::shared_ptr <cfg_set> get_follow_set ();
    bool is_ll_1 ();
    const std::unordered_set <cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator>
                                 & get_cfg_symbols () const;
    void set_cfg_symbols (
        const std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> & cfg_symbols);
    void set_terminals(const std::vector<cfg_symbol> &terminals);
    void set_start_symbol(const cfg_symbol &start_symbol);

    /** Getters **/
    std::vector <cfg_symbol> get_non_terminals ();
    std::vector <cfg_symbol> get_terminals ();
    std::vector <cfg_rule> get_rules ();
    cfg_symbol get_start_symbol ();
};

#endif //COMPILER_CFG_H
