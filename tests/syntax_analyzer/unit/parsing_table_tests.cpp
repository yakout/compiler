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

<<<<<<< Updated upstream
    cfg cfg_ob = cfg ("../.././ready_ll1_cfg.bnf");
=======
    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
>>>>>>> Stashed changes
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

    parsing_table p_table = parsing_table (cfg_ob, first, follow);

    REQUIRE (p_table.get_production("E'", "+").to_string() == prod_E_dash.to_string());
    REQUIRE (p_table.get_production("T'", "*").to_string() == prod_T_dash.to_string());
    REQUIRE (p_table.get_production("F", "(").to_string() == prod_F1.to_string());
    REQUIRE (p_table.get_production("F", "id").to_string() == prod_F2.to_string());
    REQUIRE (p_table.get_production("T", "id").to_string() == prod_T.to_string());

}
