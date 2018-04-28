//
// Created by awalid on 4/25/18.
//

#include <iostream>
#include "first_set.h"
#include "../cfg.h"

first_set::first_set() = default;

const std::unordered_map<std::string, std::unordered_set<std::pair<cfg_symbol,
        cfg_production *>, pair_hasher, pair_comparator>> &first_set::get_set_map() const {
    return first_set::my_set;
}

void first_set::add_symbol(std::string key, cfg_symbol symbol, cfg_production *parent_prod) {
    first_set::my_set[key].insert(std::make_pair(symbol, parent_prod));
}

bool first_set::has_eps(std::string symbol) {
    for(auto sym : first_set::my_set[symbol]) {
        if (sym.first.get_name() == EPS) {
            return true;
        }
    }
    return false;
}

bool first_set::empty(std::string key) {
    return first_set::my_set[key].empty();
}

void first_set::print_to_console() {
    std::cout << "============================PRINTING FIRST SET==================================\n";
    for (auto elem : first_set::my_set) {
        std::cout << "FIRST(" << elem.first << ") = {";
        int cnt = 0;
        for (auto x : elem.second) {
            std::cout << x.first.get_name();
//            if (x.second != nullptr) {
//                std::cout << ", " << x.second->to_string() << ">";
//            } else {
//                std::cout << ">";
//            }
            if (cnt != elem.second.size() - 1) {
                std::cout << ", ";
            }
            cnt++;
        }
        std::cout << "}\n";
    }
    std::cout << "=================================================================================\n";
}

