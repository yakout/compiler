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

struct pair_comparator {
    bool operator () (const std::pair<cfg_symbol, cfg_production *> & p1,
                      const std::pair<cfg_symbol, cfg_production *> & p2) const {
        if (!p1.first.get_name ().compare (p2.first.get_name ()) && p1.second == p2.second)
            return true;
        return false;
    }
};

struct pair_hasher {
    std::size_t operator () (const std::pair<cfg_symbol, cfg_production *> & p) const {
        return std::hash <std::string>() (p.first.get_name()) ^ std::hash<cfg_production *>() (p.second);
    }
};

class first_set {
public:
    first_set();

    void add_symbol(std::string, cfg_symbol symbol, cfg_production *parent_prod);
    const std::unordered_map<std::string, std::unordered_set<std::pair<cfg_symbol,
            cfg_production *>, pair_hasher, pair_comparator>> &get_set_map() const;
    bool has_eps(std::string);
    bool empty(std::string);
    void print_to_console();

private:
    std::unordered_map<std::string, std::unordered_set<std::pair<cfg_symbol,
            cfg_production *>, pair_hasher, pair_comparator>> my_set;
};


#endif //COMPILER_CFG_SET_H
