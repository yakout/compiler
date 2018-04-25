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

    void add_symbol(std::string, cfg_symbol symbol, std::shared_ptr<cfg_production> parent_prod);
    const std::unordered_map<std::string, std::vector<std::pair<cfg_symbol, std::shared_ptr<cfg_production>>>> &get_set_map() const;
    bool has_eps(std::string);

private:
    std::unordered_map<std::string, std::vector<std::pair<cfg_symbol, std::shared_ptr<cfg_production>>>> my_set;
};


#endif //COMPILER_CFG_SET_H
