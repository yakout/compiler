#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/predictive_parser.h"
#include "../../../semantic_analyzer/intermediate_code_generation/semantic_rules/three_address_code.h"

#include <unordered_map>

TEST_CASE ("TEST 1") {
//    initial stack:
//    A S{print A.n1, print A.n0} $

//    A -> B S{stack[top - 1].n0 = n0, stack[top - 1].n1 = n1} S{print A.n1, print A.n0}
//    B -> 0 B1 S{[top - 1].n0 = B1.n0 + 1, [top - 1].n1 = B1.n1}
//    B -> 1 B1 S{[top - 1].n1 = B1.n1 + 1, [top - 1].n0 = B1.n0}
//    B -> '\L' @{[top - 1].n0 = 0, [top - 1].n1 = 0}


    cfg_symbol A("A", NON_TERMINAL);
    cfg_symbol B("B", NON_TERMINAL);
    cfg_symbol B1("B", NON_TERMINAL);

    cfg_symbol s_0("0", TERMINAL);
    cfg_symbol s_1("1", TERMINAL);
    cfg_symbol eps(EPS, TERMINAL);

    int ones;
    int zeros;

    // SYNTHESISE RECORDS
    cfg_symbol synthesize_record1("record_B", SYNTHESISED);
    synthesize_record1.set_action(
            [] (std::vector<cfg_symbol>& stack) {
//                stack[top - 1].n0 = n0, stack[top - 1].n1 = n1
                stack[stack.size() - 2].add_attribute("n0", stack.back().get_attribute("n0").front());
                stack[stack.size() - 2].add_attribute("n1", stack.back().get_attribute("n1").front());
            }
    );

    cfg_symbol synthesize_record2("record_A", SYNTHESISED);
    synthesize_record2.set_action(
            [&ones, &zeros] (std::vector<cfg_symbol>& stack) {
//                S{print A.n1, print A.n0}
                zeros = std::atoi(stack.back().get_attribute("n0").front().c_str());
                ones = std::atoi(stack.back().get_attribute("n1").front().c_str());
            }
    );

    cfg_symbol synthesize_record3("record_B1_0", SYNTHESISED);
    synthesize_record3.set_action(
            [] (std::vector<cfg_symbol>& stack) {
//                S{[top - 1].n0 = B1.n0 + 1, [top - 1].n1 = B1.n1}
                stack[stack.size() - 2].
                        add_attribute("n0", std::to_string(std::atoi(stack.back().get_attribute("n0").front().c_str()) + 1));
                stack[stack.size() - 2].add_attribute("n1", stack.back().get_attribute("n1").front());
            }
    );

    cfg_symbol synthesize_record4("record_B1_1", SYNTHESISED);
    synthesize_record4.set_action(
            [] (std::vector<cfg_symbol>& stack) {
                stack[stack.size() - 2].
                        add_attribute("n1", std::to_string(std::atoi(stack.back().get_attribute("n1").front().c_str()) + 1));
                stack[stack.size() - 2].add_attribute("n0", stack.back().get_attribute("n0").front());
            }
    );

    cfg_symbol action1("@action1", ACTION);
    action1.set_action(
            [] (std::vector<cfg_symbol>& stack) {
//                @{[top - 1].n0 = 0, [top - 1].n1 = 0}
                stack[stack.size() - 2].add_attribute("n0", "0");
                stack[stack.size() - 2].add_attribute("n1", "0");
            }
    );


    std::vector<cfg_symbol> A_prod_vector;

    std::vector<cfg_symbol> B_prod1_vector;
    std::vector<cfg_symbol> B_prod2_vector;
    std::vector<cfg_symbol> B_prod3_vector;

    A_prod_vector.push_back(B);
    A_prod_vector.push_back(synthesize_record1);
    A_prod_vector.push_back(synthesize_record2);

    B_prod1_vector.push_back(s_0);
    B_prod1_vector.push_back(B1);
    B_prod1_vector.push_back(synthesize_record3);


    B_prod2_vector.push_back(s_1);
    B_prod2_vector.push_back(B1);
    B_prod2_vector.push_back(synthesize_record4);

    B_prod3_vector.push_back(eps);
    B_prod3_vector.push_back(action1);

    cfg_production prod_A(A, A_prod_vector);

    cfg_production prod1_B(B, B_prod1_vector);
    cfg_production prod2_B(B, B_prod2_vector);
    cfg_production prod3_B(B, B_prod3_vector);


    std::unordered_map<std::pair<std::string, std::string>, cfg_production,
            parsing_table_hasher, parsing_table_comparator> table;

    table[{"A", "0"}] = prod_A;
    table[{"A", "1"}] = prod_A;
    table[{"A", "$"}] = prod_A;

    table[{"B", "0"}] = prod1_B;
    table[{"B", "1"}] = prod2_B;
    table[{"B", "$"}] = prod3_B;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(table);
    p_table->draw("parsing_table.txt");

    std::vector<std::string> input_buffer{
            "0",
            "1",
            "1",
            "1",
            "1",
            "1",
            "$"};

    predictive_parser parser(A, p_table, input_buffer);
    parser.parse();

    parser.write_derivations("actions.log");
    parser.write_debug_stack("debug_stack.log");

    REQUIRE(zeros == 1);
    REQUIRE(ones == 5);
}



TEST_CASE("TEST 2")
{
    cfg cfg_ob = cfg ();
    // cfg_ob.add_function ("action_1", zeros_ones_counter::action_1);
    // cfg_ob.add_function ("record_A", zeros_ones_counter::record_A);
    // cfg_ob.add_function ("record_B", zeros_ones_counter::record_B);
    // cfg_ob.add_function ("record_B1_0", zeros_ones_counter::record_B1_0);
    // cfg_ob.add_function ("record_B1_1", zeros_ones_counter::record_B1_1);



    cfg_ob.add_function ("finalize_action", three_address_code::finalize_action);

    cfg_ob.add_function ("B_action_true", three_address_code::B_action_true);
    cfg_ob.add_function ("B_action_false", three_address_code::B_action_false);
    cfg_ob.add_function ("E1_record_relop", three_address_code::E1_record_relop);
    cfg_ob.add_function ("E2_record_relop", three_address_code::E2_record_relop);
    cfg_ob.add_function ("B_action_relop", three_address_code::B_action_relop);

    cfg_ob.add_function ("B1_record_or", three_address_code::B1_record_or);
    cfg_ob.add_function ("M_record_or", three_address_code::M_record_or);
    cfg_ob.add_function ("B2_record_or", three_address_code::B2_record_or);
    cfg_ob.add_function ("B_action_or", three_address_code::B_action_or);

    cfg_ob.add_function ("B_record_if", three_address_code::B_record_if);
    cfg_ob.add_function ("M_record_if", three_address_code::M_record_if);
    cfg_ob.add_function ("S1_record_if", three_address_code::S1_record_if);
    cfg_ob.add_function ("S_action_if", three_address_code::S_action_if);

    cfg_ob.add_function ("E_action_num", three_address_code::E_action_num);

    cfg_ob.add_function ("M_action_eps", three_address_code::M_action_eps);

    cfg_ob.add_function ("S_action_assign", three_address_code::S_action_assign);


    // std::string grammar_file ("../../tests/semantic_analyzer/unit/zeros_ones_counter.bnf");
    std::string grammar_file ("../../tests/semantic_analyzer/unit/three_address_code.bnf");

    cfg_ob.parse(grammar_file);

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

//    cfg_ob.left_factor();
//    cfg_ob.remove_left_recursion();

    std::cout << "********************************" << std::endl;

    for (auto g : cfg_ob.get_grammar()) {
        std::cout << g.second.to_string() << std::endl;
    }

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(cfg_ob);
    p_table->draw("parsing_table.txt");

    cfg_ob.get_first_set()->print_to_console();
    cfg_ob.get_follow_set()->print_to_console();

    std::vector<std::string> input_buffer {
            "if",
            "(",
            "id",
            "relop",
            "id",
            "&&",
            "true",
            ")",
            "assign",
            "$"};

    predictive_parser parser(cfg_ob.get_start_symbol(), p_table, input_buffer);
    parser.parse();
}