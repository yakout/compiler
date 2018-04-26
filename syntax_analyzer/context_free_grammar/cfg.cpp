#include "cfg.h"
#include <fstream>
#include <utility>

cfg::cfg ()
    : non_terminals (), terminals (), rules () {

}

cfg::cfg (std::string grammar_file) 
    : non_terminals (), terminals (), rules () {

}

void cfg::parse (std::string grammar_file) {
    std::ifstream grammar_in_file (grammar_file.c_str ());
    // Checks if grammar file exists or not.
    if (!grammar_in_file.good ()) {
        //TODO: - Report "File doesn't exist!" error.
    }
    std::string line;
    while (std::getline (grammar_in_file, line)) {

    }
}
void cfg::add_rule () {

}

std::vector <cfg_symbol> cfg::get_non_terminals () {
    return non_terminals;
}

std::vector <cfg_symbol> cfg::get_terminals () {
    return terminals;
}

std::vector <cfg_rule> cfg::get_rules () {
    return rules;
}

cfg_symbol cfg::get_start_symbol () {
    return start_symbol;
}

bool cfg::is_ll_1 () {
    return true;
}

void
cfg::process_first_set(int prod_symbol_index, std::shared_ptr<cfg_set> first_set,
                       std::shared_ptr<cfg_production> prod) {
    if (prod_symbol_index == prod->get_symbols().size()) {
        return;
    }
    auto curr_prod_symbol = prod->get_symbols()[prod_symbol_index];
    if (curr_prod_symbol.get_type() == TERMINAL) {
        first_set->add_symbol(curr_prod_symbol.get_name(), curr_prod_symbol, prod);
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), curr_prod_symbol, prod);
        return;
    }

    // If current prod symbol isn't processed yet, process it.
    if (first_set->empty(curr_prod_symbol.get_name())) {
        // Go to curr_prod_symbol rule and iterate over all its prods and calc its first set.
        for (auto production : cfg::grammar[curr_prod_symbol].get_productions()) {
            process_first_set(0, first_set, std::shared_ptr<cfg_production>(&production));
        }
    }

    // Here curr_proc_symbol's first_set should be already processed.
    auto symbols_map = first_set->get_set_map();
    for (auto symbol : symbols_map[curr_prod_symbol.get_name()]) {
        // Add all symbols of curr_prod_symbol to lhs symbol's first set
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), symbol.first, prod);
    }

    // If curr_prod_symbol has eps in its first set, then continue processing this production.
    if (first_set->has_eps(curr_prod_symbol.get_name())) {
        process_first_set(prod_symbol_index + 1, first_set, prod);
    }
}

std::shared_ptr<cfg_set> cfg::get_first_set() {
    std::shared_ptr<cfg_set> first_set = std::make_shared<cfg_set>();

    /// Build first set
    for (auto non_terminal : cfg::non_terminals) {
        if (!first_set->empty(non_terminal.get_name())) {
            continue;
        }
        for (auto production : cfg::grammar[non_terminal].get_productions ()) { // Iterate over all productions from this non-terminal
            process_first_set(0, first_set, std::shared_ptr<cfg_production>(&production));
        }
    }
    return first_set;
}

const std::unordered_set <cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> 
                        & cfg::get_cfg_symbols () const {
    return cfg::cfg_symbols;
}

void cfg::set_cfg_symbols (
        const std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> & cfg_symbols) {
    cfg::cfg_symbols = cfg_symbols;
}

std::shared_ptr<cfg_set> cfg::get_follow_set() {
    std::shared_ptr<cfg_set> follow_set = std::make_shared<cfg_set>();
    return follow_set;
}

