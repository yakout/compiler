#include <iostream>
#include "lexical_analyzer_generator/nfa_tools/char_set.h"
#include "lexical_analyzer_generator/finite_automata/finite_automata.h"
#include "lexical_analyzer_generator/lexical_analyzer_generator.h"

std::string CALL_ERROR = "Invalid Number of Arguments";


//id = letter | digits
//
//        (0)->[eps] (1)-> [letter] (3) ->[eps]  ((5))
//           ->[eps] (2)-> [digits] (4) ->[eps]


std::shared_ptr<NFA> build_nfa()
{
    std::vector<regular_definition> v1;
    std::vector<regular_definition> v2;
    std::vector<regular_definition> v;

    regular_definition letter;
    regular_definition digits;
    regular_definition eps;

    Char_Set digits_char_set;
    digits_char_set.add_range('0', '9');

    Char_Set letters_char_set;
    letters_char_set.add_range('a', 'z');
    letters_char_set.add_range('A', 'Z');

    Char_Set empty_char_set;

    letter.name = "letter";
    letter.sequence = letters_char_set;

    digits.name = "digits";
    digits.sequence = digits_char_set;

    eps.name = "eps";
    eps.sequence = empty_char_set;

    v1.push_back(letter);
    v2.push_back(digits);
    v.push_back(eps);


    std::shared_ptr<NFA_State> s0 = std::make_shared<NFA_State>(NFA_State (0, START, v));
    std::shared_ptr<NFA_State> s1 = std::make_shared<NFA_State>(NFA_State (1, INTERMEDIATE, v1));
    std::shared_ptr<NFA_State> s2 = std::make_shared<NFA_State>(NFA_State (2, INTERMEDIATE, v2));
    std::shared_ptr<NFA_State> s3 = std::make_shared<NFA_State>(NFA_State (3, INTERMEDIATE, v));
    std::shared_ptr<NFA_State> s4 = std::make_shared<NFA_State>(NFA_State (4, INTERMEDIATE, v));
    std::shared_ptr<NFA_State> s5 = std::make_shared<NFA_State>(NFA_State (5, ACCEPTANCE, v));


    s0->insert_state (EPSILON, s1);
    s0->insert_state (EPSILON, s2);
    s1->insert_state ("a-z", s3);
    s1->insert_state ("A-Z", s3);
    s2->insert_state ("0-9", s4);
    s3->insert_state (EPSILON, s5);
    s4->insert_state (EPSILON, s5);


    std::shared_ptr<NFA> nfa(new NFA(s0, s5));
    return nfa;
}

int main(int argc, char** argv) {
    //std::shared_ptr<NFA> nfa = build_nfa();
    //nfa->visualize();
    Lexical_Analyzer_Generator generator = Lexical_Analyzer_Generator();
    generator.get_lexical_analyzer_file ("rules.txt");

    if (argc == 1)
    {

    }
    else if (argc == 2)
    {

    }
    else
    {
        std::cout << CALL_ERROR << std::endl;
    }


    return 0;
}
