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
    cfg cfg_ob = cfg ("../../tests/syntax_analyzer/unit/cfg_single_line_ll1.bnf");
    std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    /** Grammar Checking. **/
    grammar = cfg_ob.get_grammar ();

    std::cout << "********" << cfg_ob.get_start_symbol().get_name() << std::endl;
    for (auto non_t : cfg_ob.get_non_terminals())
    {
        std::cout << non_t.get_name() << std::endl;
    }
    std::cout << "********" << std::endl;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);
    p_table->draw ("parsing_table.txt");

    std::vector<std::string> input_buffer {"int",
                                           "x",
                                           ";",
                                           "if",
                                           "(",
                                           "x",
                                           ">",
                                           "2",
                                           ")",
                                           "{",
                                           "x",
                                           "=",
                                           "0",
                                           ";",
                                           "}"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
//    parser.parse();

    std::vector<std::string> stack = parser.get_debug_stack();

    for (auto s : stack)
    {
        std::cout << s << std::endl;
    }

}
