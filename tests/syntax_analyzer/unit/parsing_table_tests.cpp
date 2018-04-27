#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/parsing_table.h"


TEST_CASE("TEST 1")
{
    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod_vector;
    std::vector<cfg_symbol> E_dash_prod_vector;

    std::vector<cfg_symbol> T_prod_vector;
    std::vector<cfg_symbol> T_dash_prod_vector;

    std::vector<cfg_symbol> F_prod_vector1;
    std::vector<cfg_symbol> F_prod_vector2;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$("$", END_MARKER);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol E("E", NON_TERMINAL);
    cfg_symbol E_dash("E'", NON_TERMINAL);
    cfg_symbol T("T", NON_TERMINAL);
    cfg_symbol T_dash("T'", NON_TERMINAL);
    cfg_symbol F("F", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol multiplication("*", TERMINAL);
    cfg_symbol left_paren("(", TERMINAL);
    cfg_symbol right_paren(")", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    // E -> TE'
    E_prod_vector.push_back(T);
    E_prod_vector.push_back(E_dash);

    // E' -> +TE'
    E_dash_prod_vector.push_back(plus);
    E_dash_prod_vector.push_back(T);
    E_dash_prod_vector.push_back(E_dash);

    // T -> FT'
    T_prod_vector.push_back(F);
    T_prod_vector.push_back(T_dash);

    // T' -> *FT'
    T_dash_prod_vector.push_back(multiplication);
    T_dash_prod_vector.push_back(F);
    T_dash_prod_vector.push_back(T_dash);

    // F -> (E)
    F_prod_vector1.push_back(left_paren);
    F_prod_vector1.push_back(E);
    F_prod_vector1.push_back(right_paren);

    // F -> id
    F_prod_vector2.push_back(id);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_E(E, E_prod_vector);
    cfg_production prod_E_dash(E_dash, E_dash_prod_vector);
    cfg_production prod_E_dash_eps(E_dash, eps_vector);

    cfg_production prod_T(T, T_prod_vector);
    cfg_production prod_T_dash(T_dash, T_dash_prod_vector);
    cfg_production prod_T_dash_eps(T_dash, eps_vector);

    cfg_production prod_F1(F, F_prod_vector1);
    cfg_production prod_F2(F, F_prod_vector2);

    cfg cfg_ob = cfg ("./ready_ll1_cfg.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();


    first_set first;

    first.add_symbol("F", left_paren, &prod_F1);
    first.add_symbol("F", id, &prod_F2);

    first.add_symbol("T'", multiplication, &prod_T_dash);
    first.add_symbol("T'", eps, &prod_T_dash_eps);

    first.add_symbol("T", left_paren, &prod_T);
    first.add_symbol("T", id, &prod_T);

    first.add_symbol("E'", plus, &prod_E_dash);
    first.add_symbol("E'", eps, &prod_E_dash_eps);

    first.add_symbol("E", left_paren, &prod_E);
    first.add_symbol("E", id, &prod_E);



    follow_set follow;

    follow.add_symbol("E", s_$);
    follow.add_symbol("E", right_paren);

    follow.add_symbol("E'", s_$);
    follow.add_symbol("E'", right_paren);

    follow.add_symbol("T", plus);
    follow.add_symbol("T", s_$);
    follow.add_symbol("T", right_paren);

    follow.add_symbol("T'", plus);
    follow.add_symbol("T'", s_$);
    follow.add_symbol("T'", right_paren);

    follow.add_symbol("F", plus);
    follow.add_symbol("F", multiplication);
    follow.add_symbol("F", s_$);
    follow.add_symbol("F", right_paren);

    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
//        std::cout << "RULE KEY SYMBOL >> " << it->first.get_name () << std::endl;
//        std::cout << "RULE LHS SYMBOL AGAIN >> " << it->second.get_lhs_symbol ().get_name () << std::endl;
//        std::cout << "RULE NUMBER OF PRODUCTIONS >> " << it->second.get_productions ().size () << std::endl;
        for (std::size_t i = 0 ; i < it->second.get_productions ().size () ; i++) {
//            std::cout << "PRODUCTION # " << i << std::endl;
//            std::cout << "LHS SYMBOL >> " << it->second.get_productions ()[i].get_lhs_symbol ().get_name () << std::endl;
//            std::cout << "PRODUCTION SYMBOLS" << std::endl;
            for (std::size_t j = 0 ; j < it->second.get_productions ()[i].get_symbols ().size () ; j++) {
//                std::cout << "SYMBOL #" << j << std::endl;
//                std::cout << "SYMBOL NAME: " << it->second.get_productions ()[i].get_symbols ()[j].get_name () << std::endl;
//                std::cout << "SYMBOL TYPE: " << it->second.get_productions ()[i].get_symbols ()[j].get_type () << std::endl;
            }
        }
    }
    /** Start Symbol Checking **/
//    std::cout << "START SYMBOL NAME: " << cfg_ob.get_start_symbol ().get_name () << std::endl;
//    std::cout << "START SYMBOL TYPE: " << cfg_ob.get_start_symbol ().get_type () << std::endl;


    parsing_table p_table = parsing_table (cfg_ob, first, follow);

}