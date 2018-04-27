//
// Created by awalid on 4/25/18.
//

#ifndef COMPILER_CFG_SET_H
#define COMPILER_CFG_SET_H


#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <set>
#include "../cfg_symbol.h"

class cfg_symbol;

class cfg_set {
public:
    cfg_set();

    void add_symbol(std::string, cfg_symbol symbol, cfg_production *parent_prod);
    const std::unordered_map<std::string, std::set<std::pair<cfg_symbol,
            cfg_production *>, cfg_symbol::pair_comparator>> &get_set_map() const;
    bool has_eps(std::string);
    bool empty(std::string);

private:
    std::unordered_map<std::string, std::set<std::pair<cfg_symbol,
            cfg_production *>, cfg_symbol::pair_comparator>> my_set;
};


#endif //COMPILER_CFG_SET_H
