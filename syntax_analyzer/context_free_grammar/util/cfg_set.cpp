//
// Created by awalid on 4/25/18.
//

#include "cfg_set.h"
#include "../cfg.h"

cfg_set::cfg_set() {
}

const std::unordered_map<std::string, std::vector<cfg_symbol>> &cfg_set::get_set_map() const {
    return my_set;
}

void cfg_set::add_symbol(std::string, cfg_symbol symbol) {

}

bool cfg_set::has_eps(std::string symbol) {
    for(auto sym : cfg_set::my_set[symbol]) {
        if (sym.get_name() == EPS) {
            return true;
        }
    }
    return false;
}

