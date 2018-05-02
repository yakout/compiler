#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/context_free_grammar/cfg.h"


/**
 * utility function.
 */
bool in_ref(std::string s, std::vector<std::string> ref) 
{
    return (std::find(ref.begin(), ref.end(), s) != ref.end());
}


TEST_CASE ("longest common prefix test 1") {

    std::vector<cfg_symbol> prod1_vec;
    std::vector<cfg_symbol> prod2_vec;
    std::vector<cfg_symbol> prod3_vec;

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    cfg_symbol term1("term1", TERMINAL);
    cfg_symbol term2("term2", TERMINAL);
    cfg_symbol term3("term3", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    // S -> term1 term2 term3 | term1 term2 term3 | term1 term2 id

    prod1_vec.push_back(term1);
    prod1_vec.push_back(term2);
    prod1_vec.push_back(term3);

    prod2_vec.push_back(term1);
    prod2_vec.push_back(term2);
    prod2_vec.push_back(term3);

    prod3_vec.push_back(term1);
    prod3_vec.push_back(term2);
    prod3_vec.push_back(id);

    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1(S, prod1_vec);
    cfg_production prod2(S, prod2_vec);
    cfg_production prod3(S, prod3_vec);


    std::vector<cfg_production> prods;
    prods.push_back(prod1);
    prods.push_back(prod2);
    prods.push_back(prod3);

    REQUIRE(longest_common_prefix(prods) == 2);
}


TEST_CASE ("longest common prefix test 2") {

    std::vector<cfg_symbol> prod1_vec;
    std::vector<cfg_symbol> prod2_vec;
    std::vector<cfg_symbol> prod3_vec;

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    cfg_symbol term1("term1", TERMINAL);
    cfg_symbol term2("term2", TERMINAL);
    cfg_symbol term3("term3", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    // S -> term1 term2 term3 | term1 term2 term3 | term1 term3 id

    prod1_vec.push_back(term1);
    prod1_vec.push_back(term2);
    prod1_vec.push_back(term3);

    prod2_vec.push_back(term1);
    prod2_vec.push_back(term2);
    prod2_vec.push_back(term3);

    prod3_vec.push_back(term1);
    prod3_vec.push_back(term3);
    prod3_vec.push_back(id);

    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1(S, prod1_vec);
    cfg_production prod2(S, prod2_vec);
    cfg_production prod3(S, prod3_vec);


    std::vector<cfg_production> prods;
    prods.push_back(prod1);
    prods.push_back(prod2);
    prods.push_back(prod3);

    REQUIRE(longest_common_prefix(prods) == 1);
}


TEST_CASE ("longest common prefix test 3") {

    std::vector<cfg_symbol> prod1_vec;
    std::vector<cfg_symbol> prod2_vec;
    std::vector<cfg_symbol> prod3_vec;

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    cfg_symbol term1("term1", TERMINAL);
    cfg_symbol term2("term2", TERMINAL);
    cfg_symbol term3("term3", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    // S -> term1 term2 term3 | term2 term3 | term1 term3 id

    prod1_vec.push_back(term1);
    prod1_vec.push_back(term2);
    prod1_vec.push_back(term3);

    prod2_vec.push_back(term2);
    prod2_vec.push_back(term3);

    prod3_vec.push_back(term1);
    prod3_vec.push_back(term3);
    prod3_vec.push_back(id);

    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1(S, prod1_vec);
    cfg_production prod2(S, prod2_vec);
    cfg_production prod3(S, prod3_vec);


    std::vector<cfg_production> prods;
    prods.push_back(prod1);
    prods.push_back(prod2);
    prods.push_back(prod3);

    REQUIRE(longest_common_prefix(prods) == 0);
}


TEST_CASE ("left factoring test 1") {
    // grammar:
    // S -> if E then S | if E then S else S | a
    // E -> b

    // result:
    // S -> if E then S S' | a
    // S -> else S | eps
    // E -> b
}


TEST_CASE ("left factoring test 2") {
    // grammar:

//    X -> aE | IXE | (X)E
//    E -> IE | BXE | ϵ
//    I -> ++ | --
//    B -> + | - | ϵ

    // result:
//    steps:
//    X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//    E -> ++E ∣ --E ∣ +XE ∣ -XE ∣ XE | eps // sub x

//    X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//    E -> ++E ∣ --E ∣ +XE ∣ -XE ∣ aEE ∣ ++XEE ∣ --XEE ∣ (X)EE | eps

//     X -> aE ∣ ++XE ∣ --XE ∣ (X)E
//     E -> +E1 | -E2 | aEE | (X)EE | eps
//     E1 -> +E | XE | +XEE
//     E2 -> -E | XE | -XEE
    // we can sub X again and keep doing so we will find that this grammar is not even LL

}

#include <iostream>

TEST_CASE("left factoring test 3")
{
    std::vector<cfg_symbol> eps_vector;
    std::vector<cfg_symbol> prod1_vec;
    std::vector<cfg_symbol> prod2_vec;
    std::vector<cfg_symbol> prod3_vec;
    std::vector<cfg_symbol> prod4_vec;
    std::vector<cfg_symbol> prod5_vec;


    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);
    cfg_symbol E("E", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    cfg_symbol term1("term1", TERMINAL);
    cfg_symbol term2("term2", TERMINAL);
    cfg_symbol term3("term3", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    // S -> term1 term2 term3 | term1 term2 E | id | id + | E | eps
    // what if E -> term1 ?? // TODO
    // 
    // answer:
    // S -> term1 term2 S' | id S'' | E | \L
    // S' -> term3 | E
    // S'' -> \L | +

    prod1_vec.push_back(term1);
    prod1_vec.push_back(term2);
    prod1_vec.push_back(term3);

    prod2_vec.push_back(term1);
    prod2_vec.push_back(term2);
    prod2_vec.push_back(E);

    prod3_vec.push_back(id);

    prod4_vec.push_back(id);
    prod4_vec.push_back(plus);

    prod5_vec.push_back(E);

    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1(S, prod1_vec);
    cfg_production prod2(S, prod2_vec);
    cfg_production prod3(S, prod3_vec);
    cfg_production prod4(S, prod4_vec);
    cfg_production prod5(S, prod5_vec);
    cfg_production prod6(S, eps_vector);


    std::vector<cfg_production> prods;
    prods.push_back(prod1);
    prods.push_back(prod2);
    prods.push_back(prod3);
    prods.push_back(prod4);
    prods.push_back(prod5);
    prods.push_back(prod6);

    cfg_rule rule(S, prods);
    cfg grammar;
    grammar.add_rule(rule);

    grammar.left_factor();

    std::vector<std::string> reference_answer = {
        "S -> E | \\L | id S' | term1 term2 S''",
        "S'' -> E | term3",
        "S' -> + | \\L"};

    for (auto g : grammar.get_rules())
    {
        REQUIRE(in_ref(g.to_string(), reference_answer));
    }
}


TEST_CASE("left factoring test 4 (multi level) ")
{
    std::vector<cfg_symbol> eps_vector;
    std::vector<cfg_symbol> prod1_vec;
    std::vector<cfg_symbol> prod2_vec;
    std::vector<cfg_symbol> prod3_vec;
    std::vector<cfg_symbol> prod4_vec;
    std::vector<cfg_symbol> prod5_vec;


    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("A", NON_TERMINAL);
    cfg_symbol B("B", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol multiplication("*", TERMINAL);
    cfg_symbol left_paren("(", TERMINAL);
    cfg_symbol right_paren(")", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    cfg_symbol term1("term1", TERMINAL);
    cfg_symbol term2("term2", TERMINAL);
    cfg_symbol term3("term3", TERMINAL);

    cfg_symbol b("b", TERMINAL);
    cfg_symbol c("c", TERMINAL);
    cfg_symbol x("x", TERMINAL);
    cfg_symbol y("y", TERMINAL);
    cfg_symbol z("z", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    prod1_vec.push_back(b);
    prod1_vec.push_back(c);

    prod2_vec.push_back(b);
    prod2_vec.push_back(b);
    prod2_vec.push_back(x);

    prod3_vec.push_back(b);
    prod3_vec.push_back(b);
    prod3_vec.push_back(x);
    prod3_vec.push_back(y);

    prod4_vec.push_back(b);
    prod4_vec.push_back(b);
    prod4_vec.push_back(x);
    prod4_vec.push_back(y);
    prod4_vec.push_back(z);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1(S, prod1_vec);
    cfg_production prod2(S, prod2_vec);
    cfg_production prod3(S, prod3_vec);
    cfg_production prod4(S, prod4_vec);

    std::vector<cfg_production> prods;
    prods.push_back(prod1);
    prods.push_back(prod2);
    prods.push_back(prod3);
    prods.push_back(prod4);

    cfg_rule rule(S, prods);
    cfg grammar;
    grammar.add_rule(rule);

    grammar.left_factor();

    std::vector<std::string> reference_answer = {
        "A'' -> \\L | y A'''",
        "A''' -> \\L | z",
        "A' -> b x A'' | c",
        "A -> b A'"};

    for (auto g : grammar.get_rules())
    {
        REQUIRE(in_ref(g.to_string(), reference_answer));
    }
}


TEST_CASE ("substitution test 1")
{
    // E -> T E E + T | T E | T id | E id
    // T -> T E T * F | E F | \L

    // same as:

    // E -> T E E + T 
    // E -> T E 
    // E -> T id 
    // E -> E id 
    // T -> T E T * F 
    // T -> E F 
    // T -> ε 

    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod1_vector;
    std::vector<cfg_symbol> E_prod2_vector;
    std::vector<cfg_symbol> E_prod3_vector;
    std::vector<cfg_symbol> E_prod4_vector;

    std::vector<cfg_symbol> T_prod1_vector;
    std::vector<cfg_symbol> T_prod2_vector;
    std::vector<cfg_symbol> T_prod3_vector;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol E("E", NON_TERMINAL);
    cfg_symbol T("T", NON_TERMINAL);
    cfg_symbol F("F", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol multiplication("*", TERMINAL);
    cfg_symbol left_paren("(", TERMINAL);
    cfg_symbol right_paren(")", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    // E -> T E E + T 
    E_prod1_vector.push_back(T);
    E_prod1_vector.push_back(E);
    E_prod1_vector.push_back(E);
    E_prod1_vector.push_back(plus);
    E_prod1_vector.push_back(T);

    // E -> T E 
    E_prod2_vector.push_back(T);
    E_prod2_vector.push_back(E);

    // E -> T id 
    E_prod3_vector.push_back(T);
    E_prod3_vector.push_back(id);

    // E -> E id 
    E_prod4_vector.push_back(E);
    E_prod4_vector.push_back(id);

    // T -> T E T * F 
    T_prod1_vector.push_back(T);
    T_prod1_vector.push_back(E);
    T_prod1_vector.push_back(T);
    T_prod1_vector.push_back(multiplication);
    T_prod1_vector.push_back(F);

    // T -> E F
    T_prod2_vector.push_back(E);
    T_prod2_vector.push_back(F);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod1_E(E, E_prod1_vector);
    cfg_production prod2_E(E, E_prod2_vector);
    cfg_production prod3_E(E, E_prod3_vector);
    cfg_production prod4_E(E, E_prod4_vector);

    cfg_production prod1_T(T, T_prod1_vector);
    cfg_production prod2_T(T, T_prod2_vector);
    cfg_production prod3_T(T, eps_vector);

    std::vector<cfg_production> ruleE_productions;
    std::vector<cfg_production> ruleT_productions;

    ruleE_productions.push_back(prod1_E);
    ruleE_productions.push_back(prod2_E);
    ruleE_productions.push_back(prod3_E);
    ruleE_productions.push_back(prod4_E);

    ruleT_productions.push_back(prod1_T);
    ruleT_productions.push_back(prod2_T);
    ruleT_productions.push_back(prod3_T);

    cfg_rule ruleE(E, ruleE_productions);
    cfg_rule ruleT(T, ruleT_productions);

    cfg_rule rule = substitue(ruleE, ruleT);

    std::string ref_string = 
    "T -> T E T * F | T E E + T F | T E F | T id F | E id F | \\L";

    REQUIRE(rule.to_string() == ref_string);
}

TEST_CASE ("complex left recursion test 1") 
{

// Before LL1: 
// E -> T E E + T 
// E -> T E 
// E -> T id 
// E -> E id 
// T -> T E T * F 
// T -> E F 
// T -> ε 
// F -> ( E ) 
// F -> id 
    
// This grammar will be converted by cfg parser to this:
// E -> T E E + T | T E | T id | E id
// T -> T E T * F | E F | \L
// F -> ( E ) | id

    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/complex_left_rec.bnf");

    // cfg_ob.left_factor();
    // cfg_ob.remove_left_recursion();

    std::vector<std::string> reference_answer = {
        "F -> ( E ) | id",
        "E''' -> id E''' | F T' E' E''' | \\L",
        "T' -> E T * F T' | \\L",
        "T -> E F T' | T'",
        "E'' -> E + T | \\L",
        "E' -> T' E' E''' E'' | id",
        "E -> T' E' E'''"};

    for (auto g : cfg_ob.get_rules())
    {
        // REQUIRE(in_ref(g.to_string(), reference_answer));
    }
}
