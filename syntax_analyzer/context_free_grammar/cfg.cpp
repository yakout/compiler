#include "cfg.h"
#include <fstream>


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

std::shared_ptr <cfg_set> cfg::get_first_set () {
    std::shared_ptr<cfg_set> first_set = std::make_shared<cfg_set>();
    /// Build first set
    for (auto symbol : cfg_symbols) {
        if (symbol.get_type() == TERMINAL) {
            first_set->add_symbol(symbol.get_name(), symbol);
        } else if (symbol.get_type() == NON_TERMINAL) {
//            if (symbol.has_eps_prod()) {

//            }
        }
    }
    return first_set;
}

const std::unordered_set <cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> 
                        & cfg::get_cfg_symbols () const {
    return cfg_symbols;
}

void cfg::set_cfg_symbols (
        const std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> & cfg_symbols) {
    cfg::cfg_symbols = cfg_symbols;
}
