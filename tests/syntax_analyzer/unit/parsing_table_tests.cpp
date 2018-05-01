#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/parsing_table.h"

TEST_CASE("Parsing Table Construction Test 1")
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

    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
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
    REQUIRE (p_table.get_production("T", "id").to_string() == prod_T.to_string());
    REQUIRE (p_table.get_production("F", "id").to_string() == prod_F2.to_string());

}



TEST_CASE("Parsing Table Construction Test 1 (SYNCH)")
{
    std::vector<cfg_symbol> eps_vector;
    std::vector<cfg_symbol> empty_vector;

    std::vector<cfg_symbol> S_prod_vector_1;
    std::vector<cfg_symbol> S_prod_vector_2;

    std::vector<cfg_symbol> A_prod_vector_1;
    std::vector<cfg_symbol> A_prod_vector_2;


    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$("$", END_MARKER);
    cfg_symbol synch(SYNCH);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);
    cfg_symbol A("A", NON_TERMINAL);


    // TERMINALS SYMBOLS
    cfg_symbol a("a", TERMINAL);
    cfg_symbol b("b", TERMINAL);
    cfg_symbol c("c", TERMINAL);
    cfg_symbol d("d", TERMINAL);
    cfg_symbol e("e", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    S_prod_vector_1.push_back(A);
    S_prod_vector_1.push_back(b);
    S_prod_vector_1.push_back(S);

    S_prod_vector_2.push_back(e);

    A_prod_vector_2.push_back(c);
    A_prod_vector_2.push_back(A);
    A_prod_vector_2.push_back(d);

    A_prod_vector_1.push_back(a);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_S1(S, S_prod_vector_1);
    cfg_production prod_S2(S, S_prod_vector_2);
    cfg_production prod_S_eps(S, eps_vector);

    cfg_production prod_A1(A, A_prod_vector_1);
    cfg_production prod_A2(A, A_prod_vector_2);

    cfg_production  synch_prod(synch, empty_vector);

    // ****************************************************************

    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ll1_cfg_with_synch.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();

    first_set first;

    first.add_symbol("S", a, &prod_S1);
    first.add_symbol("S", e, &prod_S2);
    first.add_symbol("S", c, &prod_S1);
    first.add_symbol("S", eps, &prod_S_eps);

    first.add_symbol("A", a, &prod_A1);
    first.add_symbol("A", c, &prod_A2);

    follow_set follow;

    follow.add_symbol("S", s_$);

    follow.add_symbol("A", b);
    follow.add_symbol("A", d);

    parsing_table p_table = parsing_table (cfg_ob, first, follow);

    REQUIRE (p_table.get_production("S", "a").to_string() == prod_S1.to_string());
    REQUIRE (p_table.get_production("S", "c").to_string() == prod_S1.to_string());
    REQUIRE (p_table.get_production("S", "e").to_string() == prod_S2.to_string());
    REQUIRE (p_table.get_production("S", "$").to_string() == prod_S_eps.to_string());

    REQUIRE (p_table.get_production("A", "a").to_string() == prod_A1.to_string());
    REQUIRE (p_table.get_production("A", "b").get_lhs_symbol().get_type() == synch_prod.get_lhs_symbol().get_type());
    REQUIRE (p_table.get_production("A", "c").to_string() == prod_A2.to_string());
    REQUIRE (p_table.get_production("A", "d").get_lhs_symbol().get_type() == synch_prod.get_lhs_symbol().get_type());

}


TEST_CASE("INVALID LL(1) Test 1")
{
    std::vector<cfg_symbol> eps_vector;
    std::vector<cfg_symbol> S_prod_vector1;
    std::vector<cfg_symbol> S_prod_vector2;
    std::vector<cfg_symbol> E_prod_vector;;
    std::vector<cfg_symbol> C_prod_vector;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$("$", END_MARKER);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);
    cfg_symbol E("E'", NON_TERMINAL);
    cfg_symbol C("C", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol i("i", TERMINAL);
    cfg_symbol t("t", TERMINAL);
    cfg_symbol a("a", TERMINAL);
    cfg_symbol e("e", TERMINAL);
    cfg_symbol b("b", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    S_prod_vector1.push_back(i);
    S_prod_vector1.push_back(C);
    S_prod_vector1.push_back(t);
    S_prod_vector1.push_back(S);
    S_prod_vector1.push_back(E);

    S_prod_vector2.push_back(a);

    E_prod_vector.push_back(e);
    E_prod_vector.push_back(S);

    C_prod_vector.push_back(b);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_S1(S, S_prod_vector1);
    cfg_production prod_S2(S, S_prod_vector2);

    cfg_production prod_E_eps(E, E_prod_vector);
    cfg_production prod_E(E, eps_vector);

    cfg_production prod_C(C, C_prod_vector);

    // ****************************************************************

    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/invalid_ll1.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();

    first_set first;

    first.add_symbol("S", i, &prod_S1);
    first.add_symbol("S", a, &prod_S2);

    first.add_symbol("E", e, &prod_E);
    first.add_symbol("E", eps, &prod_E_eps);

    first.add_symbol("C", b, &prod_C);

    follow_set follow;

    follow.add_symbol("S", s_$);
    follow.add_symbol("S", e);

    follow.add_symbol("E", s_$);
    follow.add_symbol("E", e);

    follow.add_symbol("C", t);


    REQUIRE_THROWS( parsing_table (cfg_ob, first, follow) );
}
