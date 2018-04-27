#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/context_free_grammar/cfg.h"

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
//    A -> aX | aY

    // result:
//    A -> aZ
//    Z -> X | Y
}


TEST_CASE ("left factoring test 3") {
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