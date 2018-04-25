//
// Created by awalid on 4/25/18.
//

#include "cfg_set.h"

cfg_set::cfg_set() {
    cfg_set::eps = false;
}

const std::unordered_map<std::string, std::vector<cfg_symbol>> &cfg_set::get_set_map() const {
    return my_set;
}

void cfg_set::add_symbol(std::string, cfg_symbol symbol) {

}

bool cfg_set::has_eps() {
    return eps;
}

void cfg_set::set_eps(bool eps) {
    cfg_set::eps = eps;
}
