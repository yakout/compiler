#include <iostream>
#include <vector>
#include "intermediate_code_generation/semantic_rules/zeros_ones_counter.h"
#include "intermediate_code_generation/semantic_rules/java_bytecode.h"
#include "intermediate_code_generation/semantic_rules/three_address_code.h"
#include "../syntax_analyzer/predictive_parser.h"

int main (int argc, char *argv[]) {
    cfg cfg_ob = cfg ();

    cfg_ob.add_function ("INIT_CODE", java_bytecode::INIT_CODE);
    cfg_ob.add_function ("STATEMENT_LIST_RECORD_METHOD_BODY", java_bytecode::STATEMENT_LIST_RECORD_METHOD_BODY);
    cfg_ob.add_function ("M_RECORD_METHOD_BODY", java_bytecode::M_RECORD_METHOD_BODY);
    cfg_ob.add_function ("METHOD_BODY_ACTION", java_bytecode::METHOD_BODY_ACTION);
    cfg_ob.add_function ("FINALIZE_CODE", java_bytecode::FINALIZE_CODE);

    cfg_ob.add_function ("STATMENT_RECORD_STATEMENT_LIST", java_bytecode::STATMENT_RECORD_STATEMENT_LIST);
    cfg_ob.add_function ("M_RECORD_STATEMENT_LIST", java_bytecode::M_RECORD_STATEMENT_LIST);
    cfg_ob.add_function ("STATEMENT_LIST1_RECORD_STATEMENT_LIST", java_bytecode::STATEMENT_LIST1_RECORD_STATEMENT_LIST);
    cfg_ob.add_function ("STATEMENT_LIST1_ACTION_STATEMENT_LIST", java_bytecode::STATEMENT_LIST1_ACTION_STATEMENT_LIST);

    cfg_ob.add_function ("STATEMENT_RECORD_STATEMENT_LIST1", java_bytecode::STATEMENT_RECORD_STATEMENT_LIST1);
    cfg_ob.add_function ("M_RECORD_STATEMENT_LIST1", java_bytecode::M_RECORD_STATEMENT_LIST1);
    cfg_ob.add_function ("STATEMENT_LIST1_RECORD_STATEMENT_LIST1",
                         java_bytecode::STATEMENT_LIST1_RECORD_STATEMENT_LIST1);
    cfg_ob.add_function ("STATEMENT_LIST1_ACTION_STATEMENT_LIST1",
                         java_bytecode::STATEMENT_LIST1_ACTION_STATEMENT_LIST1);

    cfg_ob.add_function ("IF_RECORD_STATEMENT", java_bytecode::IF_RECORD_STATEMENT);
    cfg_ob.add_function ("WHILE_RECORD_STATEMENT", java_bytecode::WHILE_RECORD_STATEMENT);

    cfg_ob.add_function ("PRIMITIVE_TYPE_RECORD_DECLARATION", java_bytecode::PRIMITIVE_TYPE_RECORD_DECLARATION);
    cfg_ob.add_function ("id_ACTION_DECLARATION", java_bytecode::id_ACTION_DECLARATION);
    cfg_ob.add_function ("DECLARATION_ACTION_DECLARATION", java_bytecode::DECLARATION_ACTION_DECLARATION);

    cfg_ob.add_function ("int_ACTION_PRIMITIVE_TYPE", java_bytecode::int_ACTION_PRIMITIVE_TYPE);
    cfg_ob.add_function ("float_ACTION_PRIMITIVE_TYPE", java_bytecode::float_ACTION_PRIMITIVE_TYPE);

    cfg_ob.add_function ("EXPRESSION_RECORD_IF", java_bytecode::EXPRESSION_RECORD_IF);
    cfg_ob.add_function ("M1_RECORD_IF", java_bytecode::M1_RECORD_IF);
    cfg_ob.add_function ("STATEMENT1_RECORD_IF", java_bytecode::STATEMENT1_RECORD_IF);
    cfg_ob.add_function ("GOTO_ACTION_IF", java_bytecode::GOTO_ACTION_IF);
    cfg_ob.add_function ("M2_RECORD_IF", java_bytecode::M2_RECORD_IF);
    cfg_ob.add_function ("STATEMENT2_RECORD_IF", java_bytecode::STATEMENT2_RECORD_IF);
    cfg_ob.add_function ("IF_ACTION_IF", java_bytecode::IF_ACTION_IF);

    cfg_ob.add_function ("M1_RECORD_WHILE", java_bytecode::M1_RECORD_WHILE);
    cfg_ob.add_function ("EXPRESSION_RECORD_WHILE", java_bytecode::EXPRESSION_RECORD_WHILE);
    cfg_ob.add_function ("M2_RECORD_WHILE", java_bytecode::M2_RECORD_WHILE);
    cfg_ob.add_function ("STATEMENT_RECORD_WHILE", java_bytecode::STATEMENT_RECORD_WHILE);
    cfg_ob.add_function ("WHILE_ACTION_WHILE", java_bytecode::WHILE_ACTION_WHILE);

    cfg_ob.add_function ("id_ACTION_ASSIGNMENT", java_bytecode::id_ACTION_ASSIGNMENT);
    cfg_ob.add_function ("EXPRESSION_RECORD_ASSIGNMENT", java_bytecode::EXPRESSION_RECORD_ASSIGNMENT);
    cfg_ob.add_function ("ASSIGNMENT_ACTION_ASSIGNMENT", java_bytecode::ASSIGNMENT_ACTION_ASSIGNMENT);

    cfg_ob.add_function ("id_ACTION_FACTOR", java_bytecode::id_ACTION_FACTOR);
    cfg_ob.add_function ("FACTOR_ACTION_FACTOR_id", java_bytecode::FACTOR_ACTION_FACTOR_id);
    cfg_ob.add_function ("num_ACTION_FACTOR", java_bytecode::num_ACTION_FACTOR);
    cfg_ob.add_function ("FACTOR_ACTION_FACTOR_num", java_bytecode::FACTOR_ACTION_FACTOR_num);
    cfg_ob.add_function ("SIMPLE_EXPRESSION_RECORD", java_bytecode::SIMPLE_EXPRESSION_RECORD);
    cfg_ob.add_function ("FACTOR_ACTION_FACTOR_PAREN", java_bytecode::FACTOR_ACTION_FACTOR_PAREN);
    cfg_ob.add_function ("TERM1_IN_mulop", java_bytecode::TERM1_IN_mulop);
    cfg_ob.add_function ("mulop_ACTION", java_bytecode::mulop_ACTION);
    cfg_ob.add_function ("FACTOR_RECORD_TERM1", java_bytecode::FACTOR_RECORD_TERM1);
    cfg_ob.add_function ("TERM1_ACTION_mulop", java_bytecode::TERM1_ACTION_mulop);
    cfg_ob.add_function ("TERM1_RECORD_TERM1", java_bytecode::TERM1_RECORD_TERM1);
    cfg_ob.add_function ("TERM1_IN_eps", java_bytecode::TERM1_IN_eps);
    cfg_ob.add_function ("TERM1_ACTION_eps", java_bytecode::TERM1_ACTION_eps);

    cfg_ob.add_function ("FACTOR_RECORD_TERM", java_bytecode::FACTOR_RECORD_TERM);
    cfg_ob.add_function ("TERM1_RECORD_TERM", java_bytecode::TERM1_RECORD_TERM);

    cfg_ob.add_function ("SIMPLE_EXPRESSION1_IN_addop", java_bytecode::SIMPLE_EXPRESSION1_IN_addop);
    cfg_ob.add_function ("addop_ACTION", java_bytecode::addop_ACTION);
    cfg_ob.add_function ("TERM_RECORD_SIMPLE_EXPRESSION1", java_bytecode::TERM_RECORD_SIMPLE_EXPRESSION1);
    cfg_ob.add_function ("SIMPLE_EXPRESSION1_ACTION_addop", java_bytecode::SIMPLE_EXPRESSION1_ACTION_addop);
    cfg_ob.add_function ("SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION1",
                         java_bytecode::SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION1);
    cfg_ob.add_function ("SIMPLE_EXPRESSION1_IN_eps", java_bytecode::SIMPLE_EXPRESSION1_IN_eps);
    cfg_ob.add_function ("SIMPLE_EXPRESSION1_ACTION_eps", java_bytecode::SIMPLE_EXPRESSION1_ACTION_eps);

    cfg_ob.add_function ("TERM_RECORD_SIMPLE_EXPRESSION", java_bytecode::TERM_RECORD_SIMPLE_EXPRESSION);
    cfg_ob.add_function ("SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION",
                         java_bytecode::SIMPLE_EXPRESSION1_RECORD_SIMPLE_EXPRESSION);

    cfg_ob.add_function ("EXPRESSION1_IN_relop", java_bytecode::EXPRESSION1_IN_relop);
    cfg_ob.add_function ("relop_ACTION", java_bytecode::relop_ACTION);
    cfg_ob.add_function ("SIMPLE_EXPRESSION_RECORD_EXPRESSION1", java_bytecode::SIMPLE_EXPRESSION_RECORD_EXPRESSION1);
    cfg_ob.add_function ("EXPRESSION1_ACTION_relop", java_bytecode::EXPRESSION1_ACTION_relop);

    cfg_ob.add_function ("SIMPLE_EXPRESSION_RECORD_EXPRESSION", java_bytecode::SIMPLE_EXPRESSION_RECORD_EXPRESSION);
    cfg_ob.add_function ("EXPRESSION1_RECORD_EXPRESSION", java_bytecode::EXPRESSION1_RECORD_EXPRESSION);



    // std::string grammar_file ("../../tests/semantic_analyzer/unit/zeros_ones_counter.bnf");
   std::string grammar_file ("../../tests/semantic_analyzer/unit/java_bytecode.bnf");

    cfg_ob.parse(grammar_file);

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

    std::cout << "********************************" << std::endl;

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);
    p_table->draw("parsing_table.txt");

    cfg_ob.get_first_set()->print_to_console();
    cfg_ob.get_follow_set()->print_to_console();


    token t1 = {"if", "if", 0};
    token t2 = {"(", "(", 0};
    token t3 = {"x", "id", 0};
    token t4 = {">", "relop", 0};
    token t5 = {"5", "num", 0};
    token t6 = {")", ")", 0};
    token t7 = {"{", "{", 0};
    token t8 = {"x", "id", 0};
    token t9 = {"=", "assign", 0};
    token t10 = {"2", "num", 0};
    token t11 = {"}", "}", 0};
    token t12 = {"else", "else", 0};
    token t13 = {"{", "{", 0};
    token t14 = {"x", "id", 0};
    token t15 = {"=", "assign", 0};
    token t16 = {"0", "num", 0};
    token t17 = {"}", "}", 0};

    std::vector<token> token_vec {
            t1,
            t2,
            t3,
            t4,
            t5,
            t6,
            t7,
            t8,
            t9,
            t10,
            t11,
            t12,
            t13,
            t14,
            t15,
            t16,
            t17,
    };

//    std::vector<std::string> input_buffer {
//            "if",
//            "(",
//            "x",
//            ">",
//            "5",
//            ")",
//            "{",
//            "x",
//            "=",
//            "2",
//            "}",
//            "else",
//            "{",
//            "x",
//            "=",
//            "0",
//            "}",
//            "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, token_vec);
    parser.parse();

    parser.write_derivations("actions.log");
    parser.write_debug_stack("debug_stack.log");

}
