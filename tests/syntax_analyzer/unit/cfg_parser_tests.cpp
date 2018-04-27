#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/context_free_grammar/cfg.h"

#include <map>
#include <iostream>

/**
 * Comparator for cfg_symbol class objects used for building the reference grammar.
 */
struct cfg_symbol_comparator {
   bool operator() (const cfg_symbol & a, const cfg_symbol & b) const {
       return a.get_name () > b.get_name ();
   }
};

TEST_CASE ("Problem statement's multi-line CFG test.") {

    // BUILDING REFERENCE GRAMMAR & CFG symbol's production.

    std::map <cfg_symbol, cfg_rule, cfg_symbol_comparator> ref_grammar;
    std::map <cfg_symbol, std::vector <cfg_production>
                            , cfg_symbol_comparator> ref_symbol_productions;

    // BUILDING SYMBOLS

    // BUILDING NON TERMINAL SYMBOLS

    cfg_symbol METHOD_BODY ("METHOD_BODY", NON_TERMINAL);
    cfg_symbol STATEMENT_LIST ("STATEMENT_LIST", NON_TERMINAL);
    cfg_symbol STATEMENT ("STATEMENT", NON_TERMINAL);
    cfg_symbol DECLARATION ("DECLARATION", NON_TERMINAL);
    cfg_symbol IF ("IF", NON_TERMINAL);
    cfg_symbol WHILE ("WHILE", NON_TERMINAL);
    cfg_symbol ASSIGNMENT ("ASSIGNMENT", NON_TERMINAL);
    cfg_symbol PRIMITIVE_TYPE ("PRIMITIVE_TYPE", NON_TERMINAL);
    cfg_symbol EXPRESSION ("EXPRESSION", NON_TERMINAL);
    cfg_symbol SIMPLE_EXPRESSION ("SIMPLE_EXPRESSION", NON_TERMINAL);
    cfg_symbol TERM ("TERM", NON_TERMINAL);
    cfg_symbol SIGN ("SIGN", NON_TERMINAL);
    cfg_symbol FACTOR ("FACTOR", NON_TERMINAL);

    // BUILDING TERMINAL SYMBOLS

    cfg_symbol id ("id", TERMINAL);
    cfg_symbol semi_colon (";", TERMINAL);
    cfg_symbol int_ ("int", TERMINAL);
    cfg_symbol float_ ("float", TERMINAL);
    cfg_symbol eps (EPS, TERMINAL);
    cfg_symbol if_ ("if", TERMINAL);
    cfg_symbol open_bracket ("(", TERMINAL);
    cfg_symbol closed_bracket (")", TERMINAL);
    cfg_symbol open_brace ("{", TERMINAL);
    cfg_symbol closed_brace ("}", TERMINAL);
    cfg_symbol else_ ("else", TERMINAL);
    cfg_symbol while_ ("while", TERMINAL);
    cfg_symbol equal_ ("=", TERMINAL);
    cfg_symbol relop ("relop", TERMINAL);
    cfg_symbol addop ("addop", TERMINAL);
    cfg_symbol mulop ("mulop", TERMINAL);
    cfg_symbol num ("num", TERMINAL);
    cfg_symbol plus_ ("+", TERMINAL);
    cfg_symbol minus_ ("-", TERMINAL);

    // BUILDING RULES

    // METHOD_BODY = STATEMENT_LIST
    std::vector <cfg_symbol> method_body_sym;
    method_body_sym.push_back (STATEMENT_LIST);
    cfg_production method_body_prod (METHOD_BODY, method_body_sym);

    std::vector <cfg_production> method_body_prod_vec;
    method_body_prod_vec.push_back (method_body_prod);

    cfg_rule method_body_rule (METHOD_BODY, method_body_prod_vec);
    
    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[METHOD_BODY] = method_body_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[STATEMENT_LIST].push_back (method_body_prod);

    // STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT

    // STATEMENT_LIST = STATEMENT
    std::vector <cfg_symbol> statement_list_sym_1;
    statement_list_sym_1.push_back (STATEMENT);
    cfg_production statement_list_prod_1 (STATEMENT_LIST, statement_list_sym_1);
    
    // STATEMENT_LIST = STATEMENT_LIST STATEMENT
    std::vector <cfg_symbol> statement_list_sym_2;
    statement_list_sym_2.push_back (STATEMENT_LIST);
    statement_list_sym_2.push_back (STATEMENT);
    cfg_production statement_list_prod_2 (STATEMENT_LIST, statement_list_sym_2);

    std::vector <cfg_production> statement_list_prod_vec;
    statement_list_prod_vec.push_back (statement_list_prod_1);
    statement_list_prod_vec.push_back (statement_list_prod_2);

    cfg_rule statement_list_rule (STATEMENT_LIST, statement_list_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[STATEMENT_LIST] = statement_list_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[STATEMENT].push_back (statement_list_prod_1);
    ref_symbol_productions[STATEMENT_LIST].push_back (statement_list_prod_2);
    ref_symbol_productions[STATEMENT].push_back (statement_list_prod_2);


    // STATEMENT = DECLARATION | IF | WHILE | ASSIGNMENT

    // STATEMENT = DECLARATION
    std::vector <cfg_symbol> statement_sym_1;
    statement_sym_1.push_back (DECLARATION);
    cfg_production statement_prod_1 (STATEMENT, statement_sym_1);

    // STATEMENT = IF
    std::vector <cfg_symbol> statement_sym_2;
    statement_sym_2.push_back (IF);
    cfg_production statement_prod_2 (STATEMENT, statement_sym_2);

    // STATEMENT = WHILE
    std::vector <cfg_symbol> statement_sym_3;
    statement_sym_3.push_back (WHILE);
    cfg_production statement_prod_3 (STATEMENT, statement_sym_3);

    // STATEMENT = ASSIGNMENT
    std::vector <cfg_symbol> statement_sym_4;
    statement_sym_4.push_back (ASSIGNMENT);
    cfg_production statement_prod_4 (STATEMENT, statement_sym_4);

    std::vector <cfg_production> statement_prod_vec;
    statement_prod_vec.push_back (statement_prod_1);
    statement_prod_vec.push_back (statement_prod_2);
    statement_prod_vec.push_back (statement_prod_3);
    statement_prod_vec.push_back (statement_prod_4);
    
    cfg_rule statement_rule (STATEMENT, statement_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[STATEMENT] = statement_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[DECLARATION].push_back (statement_prod_1);
    ref_symbol_productions[IF].push_back (statement_prod_2);
    ref_symbol_productions[WHILE].push_back (statement_prod_3);
    ref_symbol_productions[ASSIGNMENT].push_back (statement_prod_4);


    // DECLARATION = PRIMITIVE_TYPE 'id' ';'

    std::vector <cfg_symbol> declaration_sym;
    declaration_sym.push_back (PRIMITIVE_TYPE);
    declaration_sym.push_back (id);
    declaration_sym.push_back (semi_colon);
    cfg_production declaration_prod (DECLARATION, declaration_sym);

    std::vector <cfg_production> declaration_prod_vec;
    declaration_prod_vec.push_back (declaration_prod);

    cfg_rule declaration_rule (DECLARATION, declaration_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[DECLARATION] = declaration_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[PRIMITIVE_TYPE].push_back (declaration_prod);
    ref_symbol_productions[id].push_back (declaration_prod);
    ref_symbol_productions[semi_colon].push_back (declaration_prod);


    // PRIMITIVE_TYPE = 'int' | 'float' | \L

    // PRIMITIVE_TYPE = 'int'
    std::vector <cfg_symbol> primitive_type_sym_1;
    primitive_type_sym_1.push_back (int_);
    cfg_production primitive_type_prod_1 (PRIMITIVE_TYPE, primitive_type_sym_1);

    // PRIMITIVE_TYPE = 'float'
    std::vector <cfg_symbol> primitive_type_sym_2;
    primitive_type_sym_2.push_back (float_);
    cfg_production primitive_type_prod_2 (PRIMITIVE_TYPE, primitive_type_sym_2);

    // PRIMITIVE_TYPE = \L
    std::vector <cfg_symbol> primitive_type_sym_3;
    primitive_type_sym_3.push_back (eps);
    cfg_production primitive_type_prod_3 (PRIMITIVE_TYPE, primitive_type_sym_3);

    std::vector <cfg_production> primitive_type_prod_vec;
    primitive_type_prod_vec.push_back (primitive_type_prod_1);
    primitive_type_prod_vec.push_back (primitive_type_prod_2);
    primitive_type_prod_vec.push_back (primitive_type_prod_3);
    
    cfg_rule primitive_type_rule (PRIMITIVE_TYPE, primitive_type_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[PRIMITIVE_TYPE] = primitive_type_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[int_].push_back (primitive_type_prod_1);
    ref_symbol_productions[float_].push_back (primitive_type_prod_2);
    ref_symbol_productions[eps].push_back (primitive_type_prod_3);


    // IF = 'if' '(' EXPRESSION ')' '{' STATEMENT '}' 'else' '{' STATEMENT '}'

    std::vector <cfg_symbol> if_sym;
    if_sym.push_back (if_);
    if_sym.push_back (open_bracket);
    if_sym.push_back (EXPRESSION);
    if_sym.push_back (closed_bracket);
    if_sym.push_back (open_brace);
    if_sym.push_back (STATEMENT);
    if_sym.push_back (closed_brace);
    if_sym.push_back (else_);
    if_sym.push_back (open_brace);
    if_sym.push_back (STATEMENT);
    if_sym.push_back (closed_brace);
    cfg_production if_prod (IF, if_sym);

    std::vector <cfg_production> if_prod_vec;
    if_prod_vec.push_back (if_prod);

    cfg_rule if_rule (IF, if_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[IF] = if_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[if_].push_back (if_prod);
    ref_symbol_productions[open_bracket].push_back (if_prod);
    ref_symbol_productions[EXPRESSION].push_back (if_prod);
    ref_symbol_productions[closed_bracket].push_back (if_prod);
    ref_symbol_productions[open_brace].push_back (if_prod);
    ref_symbol_productions[STATEMENT].push_back (if_prod);
    ref_symbol_productions[closed_brace].push_back (if_prod);
    ref_symbol_productions[else_].push_back (if_prod);
    ref_symbol_productions[open_brace].push_back (if_prod);
    ref_symbol_productions[STATEMENT].push_back (if_prod);
    ref_symbol_productions[closed_brace].push_back (if_prod);


    // WHILE = 'while' '(' EXPRESSION ')' '{' STATEMENT '}'

    std::vector <cfg_symbol> while_sym;
    while_sym.push_back (while_);
    while_sym.push_back (open_bracket);
    while_sym.push_back (EXPRESSION);
    while_sym.push_back (closed_bracket);
    while_sym.push_back (open_brace);
    while_sym.push_back (STATEMENT);
    while_sym.push_back (closed_brace);
    cfg_production while_prod (WHILE, while_sym);

    std::vector <cfg_production> while_prod_vec;
    while_prod_vec.push_back (while_prod);

    cfg_rule while_rule (WHILE, while_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[WHILE] = while_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[while_].push_back (while_prod);
    ref_symbol_productions[open_bracket].push_back (while_prod);
    ref_symbol_productions[EXPRESSION].push_back (while_prod);
    ref_symbol_productions[closed_bracket].push_back (while_prod);
    ref_symbol_productions[open_brace].push_back (while_prod);
    ref_symbol_productions[STATEMENT].push_back (while_prod);
    ref_symbol_productions[closed_brace].push_back (while_prod);


    // ASSIGNMENT = 'id' '=' EXPRESSION ';'

    std::vector <cfg_symbol> assignment_sym;
    assignment_sym.push_back (id);
    assignment_sym.push_back (equal_);
    assignment_sym.push_back (EXPRESSION);
    assignment_sym.push_back (semi_colon);
    cfg_production assignment_prod (ASSIGNMENT, assignment_sym);

    std::vector <cfg_production> assignment_prod_vec;
    assignment_prod_vec.push_back (assignment_prod);

    cfg_rule assignment_rule (ASSIGNMENT, assignment_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[ASSIGNMENT] = assignment_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[id].push_back (assignment_prod);
    ref_symbol_productions[equal_].push_back (assignment_prod);
    ref_symbol_productions[EXPRESSION].push_back (assignment_prod);
    ref_symbol_productions[semi_colon].push_back (assignment_prod);

    // EXPRESSION = SIMPLE_EXPRESSION | SIMPLE_EXPRESSION 'relop' SIMPLE_EXPRESSION

    // EXPRESSION = SIMPLE_EXPRESSION 
    std::vector <cfg_symbol> expression_list_sym_1;
    expression_list_sym_1.push_back (SIMPLE_EXPRESSION);
    cfg_production expression_prod_1 (EXPRESSION, expression_list_sym_1);
    
    // EXPRESSION = SIMPLE_EXPRESSION 'relop' SIMPLE_EXPRESSION
    std::vector <cfg_symbol> expression_list_sym_2;
    expression_list_sym_2.push_back (SIMPLE_EXPRESSION);
    expression_list_sym_2.push_back (relop);
    expression_list_sym_2.push_back (SIMPLE_EXPRESSION);
    cfg_production expression_prod_2 (EXPRESSION, expression_list_sym_2);

    std::vector <cfg_production> expression_prod_vec;
    expression_prod_vec.push_back (expression_prod_1);
    expression_prod_vec.push_back (expression_prod_2);

    cfg_rule expression_rule (EXPRESSION, expression_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[EXPRESSION] = expression_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[SIMPLE_EXPRESSION].push_back (expression_prod_1);
    ref_symbol_productions[SIMPLE_EXPRESSION].push_back (expression_prod_2);
    ref_symbol_productions[relop].push_back (expression_prod_2);
    ref_symbol_productions[SIMPLE_EXPRESSION].push_back (expression_prod_2);


    // SIMPLE_EXPRESSION = TERM | SIGN TERM | SIMPLE_EXPRESSION 'addop' TERM

    // SIMPLE_EXPRESSION = TERM
    std::vector <cfg_symbol> simple_expression_sym_1;
    simple_expression_sym_1.push_back (TERM);
    cfg_production simple_expression_prod_1 (SIMPLE_EXPRESSION, simple_expression_sym_1);

    // SIMPLE_EXPRESSION = SIGN TERM
    std::vector <cfg_symbol> simple_expression_sym_2;
    simple_expression_sym_2.push_back (SIGN);
    simple_expression_sym_2.push_back (TERM);
    cfg_production simple_expression_prod_2 (SIMPLE_EXPRESSION, simple_expression_sym_2);

    // SIMPLE_EXPRESSION = SIMPLE_EXPRESSION 'addop' TERM
    std::vector <cfg_symbol> simple_expression_sym_3;
    simple_expression_sym_3.push_back (SIMPLE_EXPRESSION);
    simple_expression_sym_3.push_back (addop);
    simple_expression_sym_3.push_back (TERM);
    cfg_production simple_expression_prod_3 (SIMPLE_EXPRESSION, simple_expression_sym_3);

    std::vector <cfg_production> simple_expression_prod_vec;
    simple_expression_prod_vec.push_back (simple_expression_prod_1);
    simple_expression_prod_vec.push_back (simple_expression_prod_2);
    simple_expression_prod_vec.push_back (simple_expression_prod_3);

    cfg_rule simple_expression_rule (SIMPLE_EXPRESSION, simple_expression_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[SIMPLE_EXPRESSION] = simple_expression_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[TERM].push_back (simple_expression_prod_1);
    ref_symbol_productions[SIGN].push_back (simple_expression_prod_2);
    ref_symbol_productions[TERM].push_back (simple_expression_prod_2);
    ref_symbol_productions[SIMPLE_EXPRESSION].push_back (simple_expression_prod_3);
    ref_symbol_productions[addop].push_back (simple_expression_prod_3);
    ref_symbol_productions[TERM].push_back (simple_expression_prod_3);

    // TERM = FACTOR | TERM 'mulop' FACTOR

    // TERM = FACTOR
    std::vector <cfg_symbol> term_sym_1;
    term_sym_1.push_back (FACTOR);
    cfg_production term_prod_1 (TERM, term_sym_1);

    // TERM = TERM 'mulop' FACTOR
    std::vector <cfg_symbol> term_sym_2;
    term_sym_2.push_back (TERM);
    term_sym_2.push_back (mulop);
    term_sym_2.push_back (FACTOR);
    cfg_production term_prod_2 (TERM, term_sym_2);

    std::vector <cfg_production> term_prod_vec;
    term_prod_vec.push_back (term_prod_1);
    term_prod_vec.push_back (term_prod_2);

    cfg_rule term_rule (TERM, term_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[TERM] = term_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[FACTOR].push_back (term_prod_1);
    ref_symbol_productions[TERM].push_back (term_prod_2);
    ref_symbol_productions[mulop].push_back (term_prod_2);
    ref_symbol_productions[FACTOR].push_back (term_prod_2);


    // FACTOR = 'id' | 'num' | '(' EXPRESSION ')'

    // FACTOR = 'id'
    std::vector <cfg_symbol> factor_sym_1;
    factor_sym_1.push_back (id);
    cfg_production factor_prod_1 (FACTOR, factor_sym_1);

    // FACTOR = 'num'
    std::vector <cfg_symbol> factor_sym_2;
    factor_sym_2.push_back (num);
    cfg_production factor_prod_2 (FACTOR, factor_sym_2);

    // FACTOR = '(' EXPRESSION ')'
    std::vector <cfg_symbol> factor_sym_3;
    factor_sym_3.push_back (open_bracket);
    factor_sym_3.push_back (EXPRESSION);
    factor_sym_3.push_back (closed_bracket);
    cfg_production factor_prod_3 (FACTOR, factor_sym_3);

    std::vector <cfg_production> factor_prod_vec;
    factor_prod_vec.push_back (factor_prod_1);
    factor_prod_vec.push_back (factor_prod_2);
    factor_prod_vec.push_back (factor_prod_3);

    cfg_rule factor_rule (FACTOR, factor_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[FACTOR] = factor_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[id].push_back (factor_prod_1);
    ref_symbol_productions[num].push_back (factor_prod_2);
    ref_symbol_productions[open_bracket].push_back (factor_prod_3);
    ref_symbol_productions[EXPRESSION].push_back (factor_prod_3);
    ref_symbol_productions[closed_bracket].push_back (factor_prod_3);


    // SIGN = '+' | \L | '-'

    // SIGN = '+'
    std::vector <cfg_symbol> sign_sym_1;
    sign_sym_1.push_back (plus_);
    cfg_production sign_prod_1 (SIGN, sign_sym_1);

    // SIGN = \L
    std::vector <cfg_symbol> sign_sym_2;
    sign_sym_2.push_back (eps);
    cfg_production sign_prod_2 (SIGN, sign_sym_2);

    // SIGN = '+'
    std::vector <cfg_symbol> sign_sym_3;
    sign_sym_3.push_back (minus_);
    cfg_production sign_prod_3 (SIGN, sign_sym_3);

    std::vector <cfg_production> sign_prod_vec;
    sign_prod_vec.push_back (sign_prod_1);
    sign_prod_vec.push_back (sign_prod_2);
    sign_prod_vec.push_back (sign_prod_3);

    cfg_rule sign_rule (SIGN, sign_prod_vec);

    // ADDING RULE TO REFERENCE GRAMMAR
    ref_grammar[SIGN] = sign_rule;

    // ADDING PRODUCTIONS TO CFG SYMBOL'S PRODCUTIONS.
    ref_symbol_productions[plus_].push_back (sign_prod_1);
    ref_symbol_productions[eps].push_back (sign_prod_2);
    ref_symbol_productions[minus_].push_back (sign_prod_3);

    cfg cfg_obj = cfg ("../../tests/syntax_analyzer/unit/ps_cfg_multi_line.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher
                                    , cfg_symbol::comparator> grammar;
    grammar = cfg_obj.get_grammar ();

    REQUIRE (cfg_obj.get_start_symbol ().get_name () == "METHOD_BODY");

    REQUIRE (cfg_obj.get_start_symbol ().get_type () == NON_TERMINAL);

    for (auto rule : grammar) {

        //Checks for the exitence of this rule LHS symbol in reference grammar.
        REQUIRE (ref_grammar.find (rule.first) != ref_grammar.end ());

        cfg_symbol ref_grammar_key_sym = rule.first;

        //Checks for the number of productions.
        REQUIRE (ref_grammar[ref_grammar_key_sym].get_productions ().size ()
                                    == rule.second.get_productions ().size ());

        // Checks for the correctness of the LHS symbol of each production in the rule.
        for (std::size_t i = 0 ; i < rule.second.get_productions ().size () ; i++) {

            REQUIRE (ref_grammar[ref_grammar_key_sym].get_productions ()[i].get_lhs_symbol ().get_name ()
                            == rule.second.get_productions ()[i].get_lhs_symbol ().get_name ());
            REQUIRE (rule.second.get_productions ()[i].get_lhs_symbol ().get_name () 
                            == rule.first.get_name ());
            REQUIRE (rule.second.get_productions ()[i].get_lhs_symbol ().get_type () == NON_TERMINAL);
            REQUIRE (rule.second.get_productions ()[i].get_lhs_symbol ().get_type () 
                            == rule.first.get_type ());

            // Checks for the number of symbols.
            REQUIRE (ref_grammar[ref_grammar_key_sym].get_productions ()[i].get_symbols ().size ()
                            == rule.second.get_productions ()[i].get_symbols ().size ());

            // Checks for the correctness of each symbol in the production.
            for (std::size_t j = 0 ; j < rule.second.get_productions ()[i].get_symbols ().size () ; j++) {
            
                REQUIRE (ref_grammar[ref_grammar_key_sym].get_productions ()[i].get_symbols ()[j].get_name ()
                            == rule.second.get_productions ()[i].get_symbols ()[j].get_name ());

                REQUIRE (ref_grammar[ref_grammar_key_sym].get_productions ()[i].get_symbols ()[j].get_type ()
                            == rule.second.get_productions ()[i].get_symbols ()[j].get_type ());
            }
        }
    }
    std::unordered_map<cfg_symbol, std::vector<cfg_production>
                        , cfg_symbol::hasher, cfg_symbol::comparator> symbol_productions;
    symbol_productions = cfg_obj.get_cfg_symbol_productions ();

    for (auto entry : symbol_productions) {
        //Checks for the exitence of the symbol in reference map.
        REQUIRE (ref_symbol_productions.find (entry.first) != ref_symbol_productions.end ());
        cfg_symbol ref_symbol_productions_key_sym = entry.first;
        REQUIRE (entry.second.size () == ref_symbol_productions[ref_symbol_productions_key_sym].size ());

        // Checks for the correctness of each symbol in the production.
        for (std::size_t i = 0 ; i < entry.second.size () ; i++) {
            for (std::size_t j = 0 ; j < entry.second[i].get_symbols ().size () ; j++) {
                REQUIRE (ref_symbol_productions[ref_symbol_productions_key_sym][i].get_symbols ()[j].get_name ()
                            == entry.second[i].get_symbols ()[j].get_name ());

                REQUIRE (ref_symbol_productions[ref_symbol_productions_key_sym][i].get_symbols ()[j].get_type ()
                            == entry.second[i].get_symbols ()[j].get_type ());
            }
        }
    }
}