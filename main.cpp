//#include <iostream>
//#include <memory>
//
//#include "lexical_analyzer_generator/nfa_tools/char_set.h"
//#include "lexical_analyzer_generator/finite_automata/finite_automata.h"
//#include "lexical_analyzer_generator/finite_automata/nfa.h"
//#include "lexical_analyzer_generator/finite_automata/nfa_state.h"
//
//std::string CALL_ERROR = "Invalid Number of Arguments";
//
//
////id = letter | digits
////
////        (0)->[eps] (1)-> [letter] (3) ->[eps]  ((5))
////           ->[eps] (2)-> [digits] (4) ->[eps]
//
//
//std::shared_ptr<nfa> build_nfa()
//{
//    std::vector<regular_definition> v1;
//    std::vector<regular_definition> v2;
//    std::vector<regular_definition> v;
//
//    regular_definition letter;
//    regular_definition digits;
//    regular_definition eps;
//
//    char_set digits_char_set;
//    digits_char_set.add_range('0', '9');
//
//    char_set letters_char_set;
//    letters_char_set.add_range('a', 'z');
//    letters_char_set.add_range('A', 'Z');
//
//    char_set empty_char_set;
//
//    letter.name = "letter";
//    letter.sequence = letters_char_set;
//
//    digits.name = "digits";
//    digits.sequence = digits_char_set;
//
//    eps.name = "eps";
//    eps.sequence = empty_char_set;
//
//    v1.push_back(letter);
//    v2.push_back(digits);
//    v.push_back(eps);
//
//    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, v));
//    std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, v1));
//    std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, v2));
//    std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, v));
//    std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, v));
//    std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, ACCEPTANCE, v));
//
//    s0->insert_transition (EPSILON, s1);
//    s0->insert_transition (EPSILON, s2);
//    s1->insert_transition ("a-z", s3);
//    s1->insert_transition ("A-Z", s3);
//    s2->insert_transition ("0-9", s4);
//    s3->insert_transition (EPSILON, s5);
//    s4->insert_transition (EPSILON, s5);
//
//    std::shared_ptr<nfa> built_nfa(new nfa(s0, s5));
//    return built_nfa;
//}
//
//int main(int argc, char** argv) {
//    std::shared_ptr<nfa> my_nfa = build_nfa();
//    my_nfa->visualize();
//
//    if (argc == 1)
//    {
//
//    }
//    else if (argc == 2)
//    {
//
//    }
//    else
//    {
//        std::cout << CALL_ERROR << std::endl;
//    }
//
//    return 0;
//}
