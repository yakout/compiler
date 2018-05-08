#include <iostream>
#include "parsing_table.h"
#include "predictive_parser.h"

int main (int argc, char *argv[]) {

    // cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/general_test.bnf");
    // cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/complex_left_rec.bnf");
//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/regression/test_1/ll1_cfg.bnf");
    // cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg_single_line_ll1.bnf");
    // cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ps_cfg_single_line.bnf");
//     cfg cfg_ob = cfg ("../tests/syntax_analyzer/unit/first_follow_test.bnf");
     cfg cfg_ob = cfg ("../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");

    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();


    std::cout << "++++ grammar before +++++" << std::endl;
    for (auto g : cfg_ob.get_grammar())
    {
        std::cout << g.second.to_string() << std::endl;
    }
  
    cfg_ob.left_factor();

    std::cout << "+++++ grammar after left_factoring ++++" << std::endl;
    for (auto g : cfg_ob.get_grammar())
    {
        std::cout << g.second.to_string() << std::endl;
    }

    cfg_ob.remove_left_recursion();

    std::cout << "+++++ grammar after remove_left_recursion ++++" << std::endl;
    for (auto g : cfg_ob.get_grammar())
    {
        std::cout << g.second.to_string() << std::endl;
    }
    
    std::cout << "0" << std::endl;
    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);

    std::cout << "1" << std::endl;

    cfg_ob.print_cfg_symbol_productions_map();
    cfg_ob.get_first_set()->print_to_console();
    cfg_ob.get_follow_set()->print_to_console();

    std::cout << "2" << std::endl;

    p_table->draw ("parsing_table.txt");

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
                                           // "}",
                                           "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    std::vector<std::string> stack = parser.get_debug_stack();
    std::vector<std::string> derivation = parser.get_derivations();

    parser.write_debug_stack("debug_stack.log");
    parser.write_derivations("actions_output.log");

    for (auto s : stack)
    {
        std::cout << s << std::endl;
    }

    std::cout << "***********" << std::endl;
    std::cout << "***********" << std::endl;
    std::cout << "***********" << std::endl;
    std::cout << "***********" << std::endl;

    for (auto d : derivation)
    {
        std::cout << d << std::endl;
    }
}
