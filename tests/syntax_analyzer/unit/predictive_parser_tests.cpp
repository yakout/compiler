#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/predictive_parser.h"
#include <memory>


TEST_CASE("PREDICTIVE PARSER TEST 1")
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

    std::vector<std::string> derivations = parser.get_derivations();

    std::vector<std::string> reference_derivations{"E -> T E'",
                                              "T -> F T'",
                                              "F -> id",
                                              "match: id",
                                              "T' -> \\L",
                                              "E' -> + T E'",
                                              "match: +",
                                              "T -> F T'",
                                              "F -> id",
                                              "match: id",
                                              "T' -> \\L",
                                              "E' -> \\L",
                                              "accept"};

    for (int i = 0; i < derivations.size(); ++i)
    {
        REQUIRE(derivations[i] == reference_derivations[i]);
    }
}


TEST_CASE("PREDICTIVE PARSER TEST 2 (panic mode)")
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

    std::unordered_map<std::pair<std::string, std::string>, cfg_production, parsing_table_hasher,
            parsing_table_comparator> table;

    table[{"S", "a"}] = prod_S1;
    table[{"S", "c"}] = prod_S1;
    table[{"S", "e"}] = prod_S2;
    table[{"S", "$"}] = prod_S_eps;


    table[{"A", "a"}] = prod_A1;
    table[{"A", "b"}] = synch_prod;
    table[{"A", "c"}] = prod_A2;
    table[{"A", "d"}] = synch_prod;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(table);

    std::vector<std::string> input_buffer{"c", "b", "$"};

    predictive_parser parser(S, p_table, input_buffer);
    parser.parse();

    std::vector<std::string> derivations = parser.get_derivations();
    std::vector<std::string> reference_derivations {"S -> A b S",
                                                    "A -> c A d",
                                                    "match: c",
                                                    "SYNCH (pop_stack)",
                                                    "Error: (missing d) - inserted.",
                                                    "match: b",
                                                    "S -> \\L",
                                                    "accept"};

    for (int i = 0; i < derivations.size(); ++i)
    {
        REQUIRE(derivations[i] == reference_derivations[i]);
    }
}


TEST_CASE("PREDICTIVE PARSER TEST 3 (panic mode when first char in input buffer is invalid)")
{
    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");

    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    grammar = cfg_ob.get_grammar ();

    cfg_ob.left_factor();
    cfg_ob.remove_left_recursion();

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);

    std::vector<std::string> input_buffer {"int",
                                           "id",
                                           ";",
                                           "if",
                                           "(",
                                           "id",
                                           "relop",
                                           "num",
                                           ")",
                                           "{",
                                           "id",
                                           "=",
                                           "num",
                                           ";",
                                           "}",
                                           "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    std::vector<std::string> derivations = parser.get_derivations();
    std::vector<std::string> reference_derivations
    {"Error: (illegal E) - discard int",
            "E -> id T' E'",
            "match: id",
            "Error: (illegal T') - discard ;",
            "Error: (illegal T') - discard if",
            "Error: (illegal T') - discard (",
            "Error: (illegal T') - discard id",
            "Error: (illegal T') - discard relop",
            "Error: (illegal T') - discard num",
            "T' -> \\L",
            "E' -> \\L",
            "Error: (illegal $ - discard )",
            "Error: (illegal $ - discard {",
            "Error: (illegal $ - discard id",
            "Error: (illegal $ - discard =",
            "Error: (illegal $ - discard num",
            "Error: (illegal $ - discard ;",
            "Error: (illegal $ - discard }",
            "accept"};

    for (int i = 0; i < derivations.size(); ++i)
    {
        // REQUIRE(derivations[i] == reference_derivations[i]);
    }
}



TEST_CASE("PREDICTIVE PARSER TEST 4 (ready LL1 grammar)")
{
    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg_single_line_ll1.bnf");

    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    grammar = cfg_ob.get_grammar ();

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);

    std::vector<std::string> input_buffer {"int",
                                           "id",
                                           ";",
                                           "if",
                                           "(",
                                           "id",
                                           "relop",
                                           "num",
                                           ")",
                                           "{",
                                           "id",
                                           "assign",
                                           "num",
                                           ";",
                                           "}",
                                           "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    std::vector<std::string> derivations = parser.get_derivations();
    std::vector<std::string> reference_derivations
            {"METHOD_BODY -> STATEMENT_LIST",
             "STATEMENT_LIST -> STATEMENT STATEMENT_LIST1",
             "STATEMENT -> DECLARATION",
             "DECLARATION -> PRIMITIVE_TYPE id ;",
             "PRIMITIVE_TYPE -> int",
             "match: int",
             "match: id",
             "match: ;",
             "STATEMENT_LIST1 -> STATEMENT STATEMENT_LIST1",
             "STATEMENT -> IF",
             "IF -> if ( EXPRESSION ) { STATEMENT } else { STATEMENT }",
             "match: if",
             "match: (",
             "EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION1",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> id",
             "match: id",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "EXPRESSION1 -> relop SIMPLE_EXPRESSION",
             "match: relop",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> num",
             "match: num",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "match: )",
             "match: {",
             "STATEMENT -> ASSIGNMENT",
             "ASSIGNMENT -> id assign EXPRESSION ;",
             "match: id",
             "match: assign",
             "EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION1",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> num",
             "match: num",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "EXPRESSION1 -> \\L",
             "match: ;",
             "match: }",
             "Error: (missing else) - inserted.",
             "Error: (missing {) - inserted.",
             "SYNCH (pop_stack)",
             "Error: (missing }) - inserted.",
             "STATEMENT_LIST1 -> \\L",
             "accept"};

    for (int i = 0; i < derivations.size(); ++i)
    {
        REQUIRE(derivations[i] == reference_derivations[i]);
    }
}




TEST_CASE("PREDICTIVE PARSER TEST 5 (ready LL1 grammar) (panic mode with synch)")
{
    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg_single_line_ll1.bnf");

    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    grammar = cfg_ob.get_grammar ();

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);

    std::vector<std::string> input_buffer {"int",
                                           "id",
                                           ";",
                                           "if",
                                           "(",
                                           "id",
                                           "relop",
                                           "num",
                                           ")",
                                           "{",
                                           "id",
                                           "assign",
                                           "num",
                                           ";",
                                           "}", "else", "{","}",
                                           "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    std::vector<std::string> derivations = parser.get_derivations();
    std::vector<std::string> reference_derivations
            {"METHOD_BODY -> STATEMENT_LIST",
             "STATEMENT_LIST -> STATEMENT STATEMENT_LIST1",
             "STATEMENT -> DECLARATION",
             "DECLARATION -> PRIMITIVE_TYPE id ;",
             "PRIMITIVE_TYPE -> int",
             "match: int",
             "match: id",
             "match: ;",
             "STATEMENT_LIST1 -> STATEMENT STATEMENT_LIST1",
             "STATEMENT -> IF",
             "IF -> if ( EXPRESSION ) { STATEMENT } else { STATEMENT }",
             "match: if",
             "match: (",
             "EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION1",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> id",
             "match: id",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "EXPRESSION1 -> relop SIMPLE_EXPRESSION",
             "match: relop",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> num",
             "match: num",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "match: )",
             "match: {",
             "STATEMENT -> ASSIGNMENT",
             "ASSIGNMENT -> id assign EXPRESSION ;",
             "match: id",
             "match: assign",
             "EXPRESSION -> SIMPLE_EXPRESSION EXPRESSION1",
             "SIMPLE_EXPRESSION -> TERM SIMPLE_EXPRESSION1",
             "TERM -> FACTOR TERM1",
             "FACTOR -> num",
             "match: num",
             "TERM1 -> \\L",
             "SIMPLE_EXPRESSION1 -> \\L",
             "EXPRESSION1 -> \\L",
             "match: ;",
             "match: }",
             "match: else",
             "match: {",
             "SYNCH (pop_stack)",
             "match: }",
             "STATEMENT_LIST1 -> \\L",
             "accept"};

    for (int i = 0; i < derivations.size(); ++i)
    {
        REQUIRE(derivations[i] == reference_derivations[i]);
    }
}

