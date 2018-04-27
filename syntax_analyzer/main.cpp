#include <iostream>
#include "parsing_table.h"
#include "predictive_parser.h"
#include "context_free_grammar/synch_production.h"

struct my_comparator {
    bool operator()(const std::pair<std::string, std::string> &p1,
                    const std::pair<std::string, std::string> &p2) const {
        if (!p1.first.compare (p2.first) && p1.second == p2.second)
            return true;
        return false;
    }
};

struct my_hasher {
    std::size_t operator()(const std::pair<std::string, std::string> &p) const {
        return std::hash<std::string>()(p.first) ^ std::hash<std::string>()(p.second);
    }
};

int main (int argc, char *argv[]) {
//    std::unordered_map<std::pair<std::string, std::string>, cfg_production, my_hasher, my_comparator> table;
//    cfg_production prod;
//    table[std::make_pair("id", "T")] = prod;


    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();
    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
        std::cout << "RULE KEY SYMBOL >> " << it->first.get_name () << std::endl;
        std::cout << "RULE LHS SYMBOL AGAIN >> " << it->second.get_lhs_symbol ().get_name () << std::endl;
        std::cout << "RULE NUMBER OF PRODUCTIONS >> " << it->second.get_productions ().size () << std::endl;
        for (std::size_t i = 0 ; i < it->second.get_productions ().size () ; i++) {
            std::cout << "PRODUCTION # " << i << std::endl;
            std::cout << "LHS SYMBOL >> " << it->second.get_productions ()[i].get_lhs_symbol ().get_name () << std::endl;
            std::cout << "PRODUCTION SYMBOLS" << std::endl;
            for (std::size_t j = 0 ; j < it->second.get_productions ()[i].get_symbols ().size () ; j++) {
                std::cout << "SYMBOL #" << j << std::endl;
                std::cout << "SYMBOL NAME: " << it->second.get_productions ()[i].get_symbols ()[j].get_name () << std::endl;
                std::cout << "SYMBOL TYPE: " << it->second.get_productions ()[i].get_symbols ()[j].get_type () << std::endl;
            }
        }
    }
    /** Start Symbol Checking **/
    std::cout << "START SYMBOL NAME: " << cfg_ob.get_start_symbol ().get_name () << std::endl;
    std::cout << "START SYMBOL TYPE: " << cfg_ob.get_start_symbol ().get_type () << std::endl;


    parsing_table p_table = parsing_table (cfg_ob);
    p_table.draw ("parsing_table.txt");

}
