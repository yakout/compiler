#include <iostream>
#include "parsing_table.h"
#include "context_free_grammar/cfg.h"

int main (int argc, char *argv[]) {
    cfg cfg_ob = cfg ("../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
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

//    std::vector<cfg_symbol> eps_vector;
//    std::vector<cfg_symbol> prod1_vec;
//    std::vector<cfg_symbol> prod2_vec;
//    std::vector<cfg_symbol> prod3_vec;
//    std::vector<cfg_symbol> prod4_vec;
//    std::vector<cfg_symbol> prod5_vec;
//
//
//    // SPECIAL SYMBOLS
//    cfg_symbol eps(EPS, TERMINAL);
//
//    // LHS NON_TERMINALS SYMBOLS
//    cfg_symbol S("S", NON_TERMINAL);
//    cfg_symbol E("E", NON_TERMINAL);
//
//    // TERMINALS SYMBOLS
//    cfg_symbol plus("+", TERMINAL);
//    cfg_symbol multiplication("*", TERMINAL);
//    cfg_symbol left_paren("(", TERMINAL);
//    cfg_symbol right_paren(")", TERMINAL);
//    cfg_symbol id("id", TERMINAL);
//
//    cfg_symbol term1("term1", TERMINAL);
//    cfg_symbol term2("term2", TERMINAL);
//    cfg_symbol term3("term3", TERMINAL);
//
//    // FILL THE PRODUCTIONS VECTORS **********************************
//    eps_vector.push_back(eps);
//
//    // S -> term1 term2 term3 | term1 term2 E | term1 id | id + | E | eps
//    // E -> abc
//
//    prod1_vec.push_back(term1);
//    prod1_vec.push_back(term2);
//    prod1_vec.push_back(term3);
//
//    prod2_vec.push_back(term1);
//    prod2_vec.push_back(term2);
////    prod2_vec.push_back(term3);
//    prod2_vec.push_back(E);
//
//    prod3_vec.push_back(term1);
////    prod3_vec.push_back(term2);
//    prod3_vec.push_back(id);
//
//    prod4_vec.push_back(id);
//    prod4_vec.push_back(plus);
//
//    prod5_vec.push_back(E);
//
//    // ****************************************************************
//
//    // CONSTRUCT PRODUCTION
//    cfg_production prod1(S, prod1_vec);
//    cfg_production prod2(S, prod2_vec);
//    cfg_production prod3(S, prod3_vec);
//    cfg_production prod4(S, prod4_vec);
//    cfg_production prod5(S, prod5_vec);
//    cfg_production prod6(S, eps_vector);
//
//
//    std::vector<cfg_production> prods;
//    prods.push_back(prod1);
//    prods.push_back(prod2);
//    prods.push_back(prod3);
//    prods.push_back(prod4);
//    prods.push_back(prod5);
//    prods.push_back(prod6);
//
//    cfg_rule rule(S, prods);
//    cfg grammar;
//    grammar.add_rule(rule);
//
//    grammar.left_factor();
//
//    for (auto rule : grammar.get_rules())
//    {
//        std::cout << rule.to_string() << std::endl;
//    }


//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg-multi-line.bnf");
//    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
//    /** Grammar Checking. **/
//    grammar = cfg_ob.get_grammar ();
//    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
//        std::cout << "RULE KEY SYMBOL >> " << it->first.to_string () << std::endl;
//        std::cout << "RULE LHS SYMBOL AGAIN >> " << it->second.get_lhs_symbol ().to_string () << std::endl;
//        std::cout << "RULE NUMBER OF PRODUCTIONS >> " << it->second.get_productions ().size () << std::endl;
//        for (std::size_t i = 0 ; i < it->second.get_productions ().size () ; i++) {
//            std::cout << "PRODUCTION # " << i << std::endl;
//            std::cout << "LHS SYMBOL >> " << it->second.get_productions ()[i].get_lhs_symbol ().to_string () << std::endl;
//            std::cout << "PRODUCTION SYMBOLS" << std::endl;
//            for (std::size_t j = 0 ; j < it->second.get_productions ()[i].get_symbols ().size () ; j++) {
//                std::cout << "SYMBOL #" << j << std::endl;
//                std::cout << "SYMBOL NAME: " << it->second.get_productions ()[i].get_symbols ()[j].to_string () << std::endl;
//                std::cout << "SYMBOL TYPE: " << it->second.get_productions ()[i].get_symbols ()[j].get_type () << std::endl;
//            }
//        }
//    }
//    /** Start Symbol Checking **/
//    std::cout << "START SYMBOL NAME: " << cfg_ob.get_start_symbol ().to_string () << std::endl;
//    std::cout << "START SYMBOL TYPE: " << cfg_ob.get_start_symbol ().get_type () << std::endl;
}


//    E -> TE’
//    E’ -> +TE’ | eps
//    T -> FT’
//    T’ -> *FT’ | eps
//    F -> (E) | id

//    FIRST(F) = {(,id}
//    FIRST(T’) = {*, eps}
//    FIRST(T) = {(,id}
//    FIRST(E’) = {+, eps}
//    FIRST(E) = {(,id}

//    FIRST(TE’) = {(,id}
//    FIRST(+TE’ ) = {+}
//    FIRST(eps) = {eps}
//    FIRST(FT’) = {(,id}
//    FIRST(*FT’) = {*}
//    FIRST(eps) = {eps}
//    FIRST((E)) = {(}
//    FIRST(id) = {id}
