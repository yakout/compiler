#include <memory>
#include "finite_automata.h"
#include "state.h"
#include "nfa.h"
#include "dfa.h"
#include "nfa_state.h"

#define EPSILON ""

void draw_trans_table(std::shared_ptr<dfa> dfa)
{

}

std::shared_ptr<nfa> build_nfa()
{
    std::vector<regular_definition> v1;
    std::vector<regular_definition> v2;
    std::vector<regular_definition> v;

    regular_definition char_a;
    regular_definition char_b;
    regular_definition eps;

    char_set a_char_set;
    a_char_set.add_character('a');

    char_set b_char_set;
    b_char_set.add_character('b');

    char_set empty_char_set;

    char_a.name = "a";
    char_a.sequence = a_char_set;

    char_b.name = "b";
    char_b.sequence = b_char_set;

    eps.name = "eps";
    eps.sequence = empty_char_set;

    v1.push_back(char_a);
    v2.push_back(char_b);
    v.push_back(eps);


    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, v));
    std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, v));
    std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, v1));
    std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, v));
    std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, v2));
    std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, v));
    std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, INTERMEDIATE, v));
    std::shared_ptr<nfa_state> s7 = std::make_shared<nfa_state>(nfa_state (7, INTERMEDIATE, v1));
    std::shared_ptr<nfa_state> s8 = std::make_shared<nfa_state>(nfa_state (8, INTERMEDIATE, v2));
    std::shared_ptr<nfa_state> s9 = std::make_shared<nfa_state>(nfa_state (9, INTERMEDIATE, v2));
    std::shared_ptr<nfa_state> s10 = std::make_shared<nfa_state>(nfa_state (10, ACCEPTANCE, v));

    s0->insert_state (EPSILON, s1);
    s0->insert_state (EPSILON, s7);
    s1->insert_state (EPSILON, s2);
    s1->insert_state (EPSILON, s4);
    s2->insert_state ("a", s3);
    s3->insert_state (EPSILON, s6);
    s4->insert_state ("b", s5);
    s5->insert_state (EPSILON, s6);
    s6->insert_state (EPSILON, s1);
    s6->insert_state (EPSILON, s7);
    s7->insert_state ("a", s8);
    s8->insert_state ("b", s9);
    s9->insert_state ("b", s10);

    std::vector<std::shared_ptr<state>> acceptance_states;
    acceptance_states.push_back(s10);
    std::shared_ptr<nfa> my_nfa(new nfa(s0, acceptance_states, 11));
    return my_nfa;
}

std::shared_ptr<dfa> convert_nfa_dfa(std::shared_ptr<nfa> nfa) {
    nfa->get_start_state();
    return nullptr;
}


std::shared_ptr<nfa> build_nfa2()
{
    std::vector<regular_definition> v1;
    std::vector<regular_definition> v2;

    regular_definition char_a;
    regular_definition char_b;

    char_set a_char_set;
    a_char_set.add_character('a');

    char_set b_char_set;
    b_char_set.add_character('b');

    char_a.name = "a";
    char_a.sequence = a_char_set;

    char_b.name = "b";
    char_b.sequence = b_char_set;

    v1.push_back(char_a);
    v2.push_back(char_b);

    std::shared_ptr<nfa> nfa1(new nfa(v1, 0, 1));
    std::shared_ptr<nfa> nfa2(new nfa(v2, 2, 3));

    nfa1->unify(nfa2);

    return nfa1;
}

int main(int argc, char** argv) {
    // std::shared_ptr<nfa> my_nfa = build_nfa();
    std::shared_ptr<nfa> my_nfa = build_nfa2();
    my_nfa->visualize();
//    std::shared_ptr<dfa> my_dfa = convert_nfa_dfa(my_nfa);
//    my_dfa->visualize(); // Would this work?
//    draw_trans_table(my_dfa);


    return 0;
}


