#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/predictive_parser.h"

#include <unordered_map>

TEST_CASE ("TEST 1") {
    std::map<std::string, int> shared_data;

    cfg_symbol A("A", NON_TERMINAL);
    cfg_symbol B("B", NON_TERMINAL);
    cfg_symbol B1("B", NON_TERMINAL);

    cfg_symbol s_0("0", TERMINAL);
    cfg_symbol s_1("1", TERMINAL);
    cfg_symbol eps(EPS, TERMINAL);


    // ACTIONS
    cfg_symbol action_1("@action1", ACTION);
    action_1.set_action(
            [&shared_data] {
//                std::cout << "number of one's = " << shared_data["B.n1"] << std::endl;
//                std::cout << "number of zero's = " << shared_data["B.n0"] << std::endl;
//
//                std::cout << std::endl << "**** dumping shared data: **** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );

    // SYNTHESISED ATTRIBUTES
    cfg_symbol syn_A0("A.n0", SYNTHESISED);
    syn_A0.set_action(
            [&syn_A0, &shared_data] {
                shared_data[syn_A0.get_name()] = shared_data["B.n0"];

//                std::cout << std::endl << "**** dumping shared data: **** for A0 " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );
    //
    cfg_symbol syn_A1("A.n1", SYNTHESISED);
    syn_A1.set_action(
            [&syn_A1, &shared_data] {
                shared_data[syn_A1.get_name()] = shared_data["B.n1"];

//                std::cout << std::endl << "**** dumping shared data: **** for A1" << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );
    // ************************************

    cfg_symbol syn_B_n1("B.n1", SYNTHESISED);
    syn_B_n1.set_action(
            [&syn_B_n1, &shared_data] {
                shared_data[syn_B_n1.get_name()] = shared_data["B.n1"];

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B_n1" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );
    //
    cfg_symbol syn_B_n0("B.n0", SYNTHESISED);
    syn_B_n0.set_action(
            [&syn_B_n0, &shared_data] {
                shared_data[syn_B_n0.get_name()] = shared_data["B.n0"];

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B_n0" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );

    // ************************************
    cfg_symbol syn_B1_n1_1("B.n1", SYNTHESISED);
    syn_B1_n1_1.set_action(
            [&syn_B1_n1_1, &shared_data] {
                shared_data[syn_B1_n1_1.get_name()] = shared_data["B.n1"] + 1;

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B1_n1_1" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );
    //
    cfg_symbol syn_B1_n0_0("B.n0", SYNTHESISED);
    syn_B1_n0_0.set_action(
            [&syn_B1_n0_0, &shared_data] {
                shared_data[syn_B1_n0_0.get_name()] = shared_data["B.n0"] + 1;

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B1_n0_0" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );

    // ************************************
    cfg_symbol syn_B_n1_init("B.n1", SYNTHESISED);
    syn_B_n1_init.set_action(
            [&syn_B_n1_init, &shared_data] {
                shared_data[syn_B_n1_init.get_name()] = 0;

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B_n1_init" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );
    //
    cfg_symbol syn_B_n0_init("B.n0", SYNTHESISED);
    syn_B_n0_init.set_action(
            [&syn_B_n0_init, &shared_data] {
                shared_data[syn_B_n0_init.get_name()] = 0;

//                std::cout << std::endl << "**** dumping shared data: for: " << "syn_B_n0_init" << "**** " << std::endl;
//                for (auto entry : shared_data) {
//                    std::cout << entry.first << ":" << entry.second << std::endl;
//                }
            }
    );


//    A -> B [syn_A0, syn_A1] @action1
//    B -> 0 B1 [syn_B1_n0_0] [syn_B_n1, syn_B_n0]
//    B -> 1 B1 [syn_B1_n1_1], [syn_B_n1, syn_B_n0]
//    B -> \L [syn_B_n1_init, syn_B_n0_init]

    std::vector<cfg_symbol> A_prod_vector;

    std::vector<cfg_symbol> B_prod1_vector;
    std::vector<cfg_symbol> B_prod2_vector;
    std::vector<cfg_symbol> B_prod3_vector;

    A_prod_vector.push_back(B);
    A_prod_vector.push_back(syn_A0);
    A_prod_vector.push_back(syn_A1);
    A_prod_vector.push_back(action_1);

    B_prod1_vector.push_back(s_0);
    B_prod1_vector.push_back(B1);
    B_prod1_vector.push_back(syn_B1_n0_0);
    B_prod1_vector.push_back(syn_B_n1);
    B_prod1_vector.push_back(syn_B_n0);


    B_prod2_vector.push_back(s_1);
    B_prod2_vector.push_back(B1);
    B_prod2_vector.push_back(syn_B1_n1_1);
    B_prod2_vector.push_back(syn_B_n1);
    B_prod2_vector.push_back(syn_B_n0);

    B_prod3_vector.push_back(eps);
    B_prod3_vector.push_back(syn_B_n0_init);
    B_prod3_vector.push_back(syn_B_n1_init);

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
            "0",
            "0",
            "0",
            "0",
            "$"};

    predictive_parser parser(A, p_table, input_buffer);
    parser.parse();

    REQUIRE(shared_data["B.n1"] == 5);
    REQUIRE(shared_data["B.n0"] == 5);
}