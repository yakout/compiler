//
// Created by awalid on 4/27/18.
//

#ifndef COMPILER_FOLLOW_SET_H
#define COMPILER_FOLLOW_SET_H

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <set>
#include "../cfg_symbol.h"

class cfg_symbol;

class follow_set {
public:
    follow_set();

    void add_symbol(std::string, cfg_symbol symbol);
    const std::unordered_map<std::string, std::unordered_set<cfg_symbol, cfg_symbol::hasher,
            cfg_symbol::comparator>> &get_set_map() const;
    bool has_eps(std::string);
    bool empty(std::string);
    void print_to_console();
private:
    std::unordered_map<std::string, std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator>> my_set;
};


#endif //COMPILER_FOLLOW_SET_H
