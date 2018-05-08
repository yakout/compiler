#include <iostream>
#include <vector>
#include "intermediate_code_generation/semantic_rules/zeros_ones_counter.h"
#include "../syntax_analyzer/predictive_parser.h"


template <typename Signature>
std::function<Signature> cast(void* f)
{
    return static_cast<Signature*>(f);
}

int main (int argc, char *argv[]) {
// S -> .code s, .next in
// B -> .code s, .false in, .true in

// S[S.next] -> if ( @action B[.true, .false] {B.code}) then S1 {S1.code} {S.code}

//    initial stack:
//    A S{print A.n1, print A.n0} $

//    A -> B S{stack[top - 1].n0 = n0, stack[top - 1].n1 = n1} S{print A.n1, print A.n0}
//    B -> 0 B1 S{[top - 1].n0 = B1.n0 + 1, [top - 1].n1 = B1.n1}
//    B -> 1 B1 S{[top - 1].n1 = B1.n1 + 1, [top - 1].n0 = B1.n0}
//    B -> '\L' @{[top - 1].n0 = 0, [top - 1].n1 = 0}


    cfg cfg_ob = cfg ();
//    std::function<void(std::vector<cfg_symbol> &)> f1(&zeros_ones_counter::action_1);
//    std::function<void(std::vector<cfg_symbol> &)> f2(&zeros_ones_counter::record_A);
//    std::function<void(std::vector<cfg_symbol> &)> f3(&zeros_ones_counter::record_B);
//    std::function<void(std::vector<cfg_symbol> &)> f4(&zeros_ones_counter::record_B1_0);
//    std::function<void(std::vector<cfg_symbol> &)> f5(&zeros_ones_counter::record_B1_1);

    cfg_ob.add_function ("action_1", zeros_ones_counter::action_1);
    cfg_ob.add_function ("record_A", zeros_ones_counter::record_A);
    cfg_ob.add_function ("record_B", zeros_ones_counter::record_B);
    cfg_ob.add_function ("record_B1_0", zeros_ones_counter::record_B1_0);
    cfg_ob.add_function ("record_B1_1", zeros_ones_counter::record_B1_1);

    std::string grammar_file ("../tests/semantic_analyzer/unit/zeros_ones_counter.bnf");
//    std::string grammar_file ("../tests/semantic_analyzer/unit/three_address_code.bnf");

    cfg_ob.parse(grammar_file);

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

    cfg_ob.left_factor();
    cfg_ob.remove_left_recursion();

    std::cout << "********************************" << std::endl;

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);
    p_table->draw("parsing_table.txt");

    cfg_ob.get_first_set()->print_to_console();
    cfg_ob.get_follow_set()->print_to_console();

    std::vector<std::string> input_buffer{
            "0",
            "0",
            "0",
            "0",
            "1",
            "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();

    parser.write_derivations("actions.log");
    parser.write_debug_stack("debug_stack.log");

}
