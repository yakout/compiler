//
// Created by awalid on 4/25/18.
//

#include "cfg_set.h"
#include "../cfg.h"

cfg_set::cfg_set() {
}

const std::unordered_map<std::string, std::set<std::pair<cfg_symbol,
        cfg_production *>, cfg_symbol::pair_comparator>> &cfg_set::get_set_map() const {
    return cfg_set::my_set;
}

void cfg_set::add_symbol(std::string key, cfg_symbol symbol, cfg_production *parent_prod) {
    cfg_set::my_set[key].insert(std::make_pair(symbol, parent_prod));
}

bool cfg_set::has_eps(std::string symbol) {
    for(auto sym : cfg_set::my_set[symbol]) {
        if (sym.first.get_name() == EPS) {
            return true;
        }
    }
    return false;
}

bool cfg_set::empty(std::string key) {
    return cfg_set::my_set[key].empty();
}

