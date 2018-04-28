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


//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ready_ll1_cfg.bnf");
//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg_single_line_ll1.bnf");
//    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/ps_cfg_single_line.bnf");
    cfg cfg_ob = cfg ("../tests/syntax_analyzer/unit/left_rec_left_fact.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();

    cfg_ob.left_factor();
    cfg_ob.remove_left_recursion();

    std::cout << "+++++++++" << std::endl;
    for (auto g : cfg_ob.get_grammar())
    {
        std::cout << g.second.to_string() << std::endl;
    }
    std::cout << "+++++++++" << std::endl;


    std::cout << "********" << cfg_ob.get_start_symbol().get_name() << std::endl;
    for (auto non_t : cfg_ob.get_non_terminals())
    {
        std::cout << non_t.get_name() << std::endl;
    }
    std::cout << "********" << std::endl;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);

    cfg_ob.print_cfg_symbol_productions_map();
    cfg_ob.get_first_set()->print_to_console();
    cfg_ob.get_follow_set()->print_to_console();

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
                                           "=",
                                           "num",
                                           ";",
                                           "}", "else", "{","}",
                                           "}",
                                           "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    std::vector<std::string> stack = parser.get_debug_stack();
    std::vector<std::string> derivation = parser.get_derivations();

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
