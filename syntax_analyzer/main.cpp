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

//    std::vector<cfg_symbol> eps_vector;
//
//    std::vector<cfg_symbol> E_prod_vector;
//    std::vector<cfg_symbol> E_dash_prod_vector;
//
//    std::vector<cfg_symbol> T_prod_vector;
//    std::vector<cfg_symbol> T_dash_prod_vector;
//
//    std::vector<cfg_symbol> F_prod_vector1;
//    std::vector<cfg_symbol> F_prod_vector2;
//
//    // SPECIAL SYMBOLS
//    cfg_symbol eps(EPS, TERMINAL);
//    cfg_symbol s_$("$", END_MARKER);
//
//    // LHS NON_TERMINALS SYMBOLS
//    cfg_symbol E("E", NON_TERMINAL);
//    cfg_symbol E_dash("E'", NON_TERMINAL);
//    cfg_symbol T("T", NON_TERMINAL);
//    cfg_symbol T_dash("T'", NON_TERMINAL);
//    cfg_symbol F("F", NON_TERMINAL);
//
//    // TERMINALS SYMBOLS
//    cfg_symbol plus("+", TERMINAL);
//    cfg_symbol multiplication("*", TERMINAL);
//    cfg_symbol left_paren("(", TERMINAL);
//    cfg_symbol right_paren(")", TERMINAL);
//    cfg_symbol id("id", TERMINAL);
//
//    // FILL THE PRODUCTIONS VECTORS **********************************
//    eps_vector.push_back(eps);
//
//    // E -> TE'
//    E_prod_vector.push_back(T);
//    E_prod_vector.push_back(E_dash);
//
//    // E' -> +TE'
//    E_dash_prod_vector.push_back(plus);
//    E_dash_prod_vector.push_back(T);
//    E_dash_prod_vector.push_back(E_dash);
//
//    // T -> FT'
//    T_prod_vector.push_back(F);
//    T_prod_vector.push_back(T_dash);
//
//    // T' -> *FT'
//    T_dash_prod_vector.push_back(multiplication);
//    T_dash_prod_vector.push_back(F);
//    T_dash_prod_vector.push_back(T_dash);
//
//    // F -> (E)
//    F_prod_vector1.push_back(left_paren);
//    F_prod_vector1.push_back(E);
//    F_prod_vector1.push_back(right_paren);
//
//    // F -> id
//    F_prod_vector2.push_back(id);
//    // ****************************************************************
//
//    // CONSTRUCT PRODUCTION
//    cfg_production prod_E(E, E_prod_vector);
//    cfg_production prod_E_dash(E_dash, E_dash_prod_vector);
//    cfg_production prod_E_dash_eps(E_dash, eps_vector);
//
//    cfg_production prod_T(T, T_prod_vector);
//    cfg_production prod_T_dash(T_dash, T_dash_prod_vector);
//    cfg_production prod_T_dash_eps(T_dash, eps_vector);
//
//    cfg_production prod_F1(F, F_prod_vector1);
//    cfg_production prod_F2(F, F_prod_vector2);
//
//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
//    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
//    /** Grammar Checking. **/
//    grammar = cfg_ob.get_grammar ();
//
//
//    first_set first;
//
//    first.add_symbol("F", left_paren, &prod_F1);
//    first.add_symbol("F", id, &prod_F2);
//
//    first.add_symbol("T'", multiplication, &prod_T_dash);
//    first.add_symbol("T'", eps, &prod_T_dash_eps);
//
//    first.add_symbol("T", left_paren, &prod_T);
//    first.add_symbol("T", id, &prod_T);
//
//    first.add_symbol("E'", plus, &prod_E_dash);
//    first.add_symbol("E'", eps, &prod_E_dash_eps);
//
//    first.add_symbol("E", left_paren, &prod_E);
//    first.add_symbol("E", id, &prod_E);
//
//
//
//
//
//
////    FOLLOW(E) = { $, ) }
////    FOLLOW(E’) = { $, ) }
////    FOLLOW(T) = { +, ), $ }
////    FOLLOW(T’) = { +, ), $ }
////    FOLLOW(F) = {+, *, ), $ }
//
//    follow_set follow;
//
//    follow.add_symbol("E", s_$);
//    follow.add_symbol("E", right_paren);
//
//    follow.add_symbol("E'", s_$);
//    follow.add_symbol("E'", right_paren);
//
//    follow.add_symbol("T", plus);
//    follow.add_symbol("T", s_$);
//    follow.add_symbol("T", right_paren);
//
//    follow.add_symbol("T'", plus);
//    follow.add_symbol("T'", s_$);
//    follow.add_symbol("T'", right_paren);
//
//    follow.add_symbol("F", plus);
//    follow.add_symbol("F", multiplication);
//    follow.add_symbol("F", s_$);
//    follow.add_symbol("F", right_paren);
//
//    for (auto it = grammar.begin(); it != grammar.end(); ++it) {
//        std::cout << "RULE KEY SYMBOL >> " << it->first.get_name () << std::endl;
//        std::cout << "RULE LHS SYMBOL AGAIN >> " << it->second.get_lhs_symbol ().get_name () << std::endl;
//        std::cout << "RULE NUMBER OF PRODUCTIONS >> " << it->second.get_productions ().size () << std::endl;
//        for (std::size_t i = 0 ; i < it->second.get_productions ().size () ; i++) {
//            std::cout << "PRODUCTION # " << i << std::endl;
//            std::cout << "LHS SYMBOL >> " << it->second.get_productions ()[i].get_lhs_symbol ().get_name () << std::endl;
//            std::cout << "PRODUCTION SYMBOLS" << std::endl;
//            for (std::size_t j = 0 ; j < it->second.get_productions ()[i].get_symbols ().size () ; j++) {
//                std::cout << "SYMBOL #" << j << std::endl;
//                std::cout << "SYMBOL NAME: " << it->second.get_productions ()[i].get_symbols ()[j].get_name () << std::endl;
//                std::cout << "SYMBOL TYPE: " << it->second.get_productions ()[i].get_symbols ()[j].get_type () << std::endl;
//            }
//        }
//    }
//    /** Start Symbol Checking **/
//    std::cout << "START SYMBOL NAME: " << cfg_ob.get_start_symbol ().get_name () << std::endl;
//    std::cout << "START SYMBOL TYPE: " << cfg_ob.get_start_symbol ().get_type () << std::endl;
//
//
//    parsing_table p_table = parsing_table (cfg_ob, first, follow);
//
//
//    p_table.draw ("parsing_table.txt");
//
//    std::vector<std::string> input_buffer{"id", "+", "id", "$"};
//
//    predictive_parser parser(E, std::make_shared<parsing_table>(p_table), input_buffer);
//
//    parser.parse();
//
//
//    for (std::string s : parser.get_derivations())
//    {
//        std::cout << s << std::endl;
//    }


    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod_vector;
    std::vector<cfg_symbol> E_dash_prod_vector;

    std::vector<cfg_symbol> T_prod_vector;
    std::vector<cfg_symbol> T_dash_prod_vector;

    std::vector<cfg_symbol> F_prod_vector1;
    std::vector<cfg_symbol> F_prod_vector2;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$(END_MARKER);

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

    std::unordered_map<std::pair<std::string, std::string>, cfg_production, parsing_table_hasher, parsing_table_comparator> table;

    table[{"E", "id"}] = prod_E;
    table[{"E", "("}] = prod_E;

    table[{"E'", "+"}] = prod_E_dash;
    table[{"E'", ")"}] = prod_E_dash_eps;
    table[{"E'", "$"}] = prod_E_dash_eps;

    table[{"T", "id"}] = prod_T;
    table[{"T", "("}] = prod_T;

    table[{"T'", "+"}] = prod_T_dash_eps;
    table[{"T'", "*"}] = prod_T_dash;
    table[{"T'", ")"}] = prod_T_dash_eps;
    table[{"T'", "$"}] = prod_T_dash_eps;

    table[{"F", "("}] = prod_F1;
    table[{"F", "id"}] = prod_F2;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(table);

    std::vector<std::string> input_buffer{"id", "+", "id", "$"};

    predictive_parser parser(E, p_table, input_buffer);
    parser.parse();

    std::vector<std::string> derivations = parser.get_debug_stack();

    for (auto s : derivations)
    {
        std::cout << s << std::endl;
    }




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
//    cfg_symbol S("A", NON_TERMINAL);
//    cfg_symbol B("B", NON_TERMINAL);
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
//    cfg_symbol b("b", TERMINAL);
//    cfg_symbol c("c", TERMINAL);
//    cfg_symbol x("x", TERMINAL);
//    cfg_symbol y("y", TERMINAL);
//    cfg_symbol z("z", TERMINAL);
//
//    // FILL THE PRODUCTIONS VECTORS **********************************
//    eps_vector.push_back(eps);
//
//    // S -> term1 term2 term3 | term1 term2 E | id | id + | E | eps
//    // E -> abc
//
//    prod1_vec.push_back(b);
//    prod1_vec.push_back(c);
////    prod1_vec.push_back(term3);
//
//    prod2_vec.push_back(b);
//    prod2_vec.push_back(b);
//    prod2_vec.push_back(x);
////    prod2_vec.push_back(term3);
////    prod2_vec.push_back(E);
//
////    prod3_vec.push_back(term1);
////    prod3_vec.push_back(term2);
//    prod3_vec.push_back(b);
//    prod3_vec.push_back(b);
//    prod3_vec.push_back(x);
//    prod3_vec.push_back(y);
//
//    prod4_vec.push_back(b);
//    prod4_vec.push_back(b);
//    prod4_vec.push_back(x);
//    prod4_vec.push_back(y);
//    prod4_vec.push_back(z);
//
////    prod5_vec.push_back(E);
//
//    // ****************************************************************
//
//    // CONSTRUCT PRODUCTION
//    cfg_production prod1(S, prod1_vec);
//    cfg_production prod2(S, prod2_vec);
//    cfg_production prod3(S, prod3_vec);
//    cfg_production prod4(S, prod4_vec);
////    cfg_production prod5(S, prod5_vec);
////    cfg_production prod6(S, eps_vector);
//
//
//    std::vector<cfg_production> prods;
//    prods.push_back(prod1);
//    prods.push_back(prod2);
//    prods.push_back(prod3);
//    prods.push_back(prod4);
////    prods.push_back(prod5);
////    prods.push_back(prod6);
//
//    cfg_rule rule(S, prods);
//    cfg grammar;
//    grammar.add_rule(rule);
//
//    grammar.left_factor();
////    S -> term1 term2 term3 | term1 term2 E | term1 id | id + | E | \L
//
//    /**
//     *
//     * S -> term S1 | id + | E | \L
//     * S1 -> term2 term3 | term2 E | id
//     *
//     */
//
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
