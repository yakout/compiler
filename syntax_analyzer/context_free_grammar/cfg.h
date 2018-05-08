#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "cfg_rule.h"
#include "util/first_set.h"
#include "util/follow_set.h"
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <unordered_map>
#include <functional>

#define EPS "\\L"

/**
 * utility function used in left factoring
 */
int longest_common_prefix(std::vector<cfg_production> prods);
/**
 * substitues rule1 in rule2
 * 
 * @return the new resulting rule
 */
cfg_rule substitue(cfg_rule rule1, cfg_rule rule2);

class cfg {
private:
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> non_terminals;
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> terminals;
    cfg_symbol start_symbol;
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> cfg_symbol_productions;

    std::unordered_map<std::string, std::function<void(std::vector<cfg_symbol> &)>&> functions;

    void process_first_set(int prod_symbol_index, std::shared_ptr<first_set> first_set,
                           cfg_production *prod);
    void process_follow_set(cfg_symbol non_terminal, std::shared_ptr<follow_set> follow_set);

    void parse_rule (std::string &, bool);

    void update_rule (std::vector<cfg_production> &);

public:
    cfg ();
    explicit cfg (std::string);

    void parse (std::string &);
    const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &
    get_cfg_symbol_productions() const;

    void print_cfg_symbol_productions_map();
    void set_cfg_symbol_productions(
            const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &cfg_symbol_productions);
    const std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> &get_grammar() const;
    void set_non_terminals(const std::unordered_set<cfg_symbol
            , cfg_symbol::hasher, cfg_symbol::comparator> &);
    void
    set_grammar(const std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> &);
    std::shared_ptr <first_set> get_first_set ();
    std::shared_ptr <follow_set> get_follow_set ();
    void add_rule (cfg_symbol &, std::vector<cfg_production> &);
    void add_rule (cfg_rule &);
    void set_terminals(const std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> &terminals);
    void set_start_symbol(const cfg_symbol &start_symbol);
    void add_function(std::string name, std::function<void(std::vector<cfg_symbol> &)> func);

    /** Grammar Correction **/
    void left_factor ();
    void remove_left_recursion ();

    /** Getters **/
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> get_non_terminals ();
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> get_terminals ();
    cfg_symbol get_start_symbol ();
    std::vector <cfg_rule> get_rules ();

    bool is_last_symbol(int pos, cfg_production production);

    int get_next_sym_pos(int pos, cfg_production production);
};

#endif //COMPILER_CFG_H