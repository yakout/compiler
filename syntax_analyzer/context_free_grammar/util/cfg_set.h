//
// Created by awalid on 4/25/18.
//

#ifndef COMPILER_CFG_SET_H
#define COMPILER_CFG_SET_H


#include <unordered_map>
#include <vector>
#include "../cfg_symbol.h"

class cfg_symbol;

class cfg_set {
public:
    cfg_set();

    void add_symbol(std::string, cfg_symbol symbol);
    const std::unordered_map<std::string, std::vector<cfg_symbol>> &get_set_map() const;

private:
    std::unordered_map<std::string, std::vector<cfg_symbol>> my_set;
};


#endif //COMPILER_CFG_SET_H
