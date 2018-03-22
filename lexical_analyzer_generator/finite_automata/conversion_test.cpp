#include <iostream>
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
    char_set a_char_set;
    a_char_set.add_character('a');

    char_set b_char_set;
    b_char_set.add_character('b');

    char_set eps;


    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
    std::shared_ptr<nfa_state> s1 = std::make_shared<nfa_state>(nfa_state (1, INTERMEDIATE, eps));
    std::shared_ptr<nfa_state> s2 = std::make_shared<nfa_state>(nfa_state (2, INTERMEDIATE, a_char_set));
    std::shared_ptr<nfa_state> s3 = std::make_shared<nfa_state>(nfa_state (3, INTERMEDIATE, eps));
    std::shared_ptr<nfa_state> s4 = std::make_shared<nfa_state>(nfa_state (4, INTERMEDIATE, b_char_set));
    std::shared_ptr<nfa_state> s5 = std::make_shared<nfa_state>(nfa_state (5, INTERMEDIATE, eps));
    std::shared_ptr<nfa_state> s6 = std::make_shared<nfa_state>(nfa_state (6, INTERMEDIATE, eps));
    std::shared_ptr<nfa_state> s7 = std::make_shared<nfa_state>(nfa_state (7, INTERMEDIATE, a_char_set));
    std::shared_ptr<nfa_state> s8 = std::make_shared<nfa_state>(nfa_state (8, INTERMEDIATE, b_char_set));
    std::shared_ptr<nfa_state> s9 = std::make_shared<nfa_state>(nfa_state (9, INTERMEDIATE, b_char_set));
    std::shared_ptr<nfa_state> s10 = std::make_shared<nfa_state>(nfa_state (10, ACCEPTANCE, eps));

    s0->insert_transition (EPSILON, s1);
    s0->insert_transition (EPSILON, s7);
    s1->insert_transition (EPSILON, s2);
    s1->insert_transition (EPSILON, s4);
    s2->insert_transition ("a", s3);
    s3->insert_transition (EPSILON, s6);
    s4->insert_transition ("b", s5);
    s5->insert_transition (EPSILON, s6);
    s6->insert_transition (EPSILON, s1);
    s6->insert_transition (EPSILON, s7);
    s7->insert_transition ("a", s8);
    s8->insert_transition ("b", s9);
    s9->insert_transition ("b", s10);

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
    char_set a_char_set;
    a_char_set.add_character('a');

    char_set b_char_set;
    b_char_set.add_character('b');

    std::shared_ptr<nfa> nfa1(new nfa(a_char_set, 1, 2));
    std::shared_ptr<nfa> nfa2(new nfa(b_char_set, 3, 4));

    nfa2->plus();
    nfa1->concat(nfa2);
    nfa1->concat(nfa1);

    return nfa1;
}

std::shared_ptr<nfa> build_nfa3()
{
  char_set a_char_set = char_set();
  a_char_set.add_character ('a');

  char_set b_char_set = char_set();
  b_char_set.add_character ('b');
  std::shared_ptr <nfa> nfa_a_ptr (new nfa(a_char_set, "a"));
  std::shared_ptr<nfa> nfa_b_ptr(new nfa(b_char_set, "b"));

  nfa_a_ptr->unify (nfa_b_ptr);

  return nfa_a_ptr;
}

int main(int argc, char** argv) {
//    std::shared_ptr<nfa> my_nfa = build_nfa();
    std::shared_ptr<nfa> my_nfa = build_nfa3();
    my_nfa->visualize();

//    std::shared_ptr<dfa> my_dfa = convert_nfa_dfa(my_nfa);
//    my_dfa->visualize(); // Would this work?
//    draw_trans_table(my_dfa);


    return 0;
}
