//#include "../../lexical_analyzer/lexical_analyzer.h"
//#include <iostream>
//
//int main () {
//    std::string transition_table_file = "tests/lexical_analyzer/transition_table.txt";
//    std::string code_file = "tests/lexical_analyzer/code.c";
//
//    lexical_analyzer *lex = new lexical_analyzer (transition_table_file, code_file);
//
//    std::vector<std::shared_ptr<dfa_state>> vec;
//    vec = lex->get_dfa ()->get_dfa_states ();
//
//    std::cout << "Number of states: " << vec.size () << std::endl;
//
//    std::cout << "--------------------------" << std::endl;
//
//     for (int i=0 ; i < vec.size () ; i++) {
//        std::cout << "State ID: " <<vec[i]->get_id() << " State Type: "
//                        << vec[i]->get_type() << " State Token Class: " << vec[i]->get_token_class () << std::endl;
//    }
//
//    std::cout << "--------------------------" << std::endl;
//
//    lex->get_dfa ()->visualize ();
//}