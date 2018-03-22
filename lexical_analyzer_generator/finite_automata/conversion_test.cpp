#include <iostream>
#include <memory>
#include <queue>
#include <iostream>
#include <set>

#include "finite_automata.h"
#include "state.h"
#include "nfa.h"
#include "dfa.h"
#include "nfa_state.h"
#include "dfa_state.h"
#include "../nfa_tools/regex_processor.h"

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

std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states,
                                              regular_definition inp)
{
    std::set<std::shared_ptr<nfa_state>> reachable_states;
    for (const auto &state : nfa_states)
    {
        auto trans_map = state->get_transitions();
        std::vector<std::shared_ptr<nfa_state>> curr_reached = trans_map[inp.name];
        for (const auto &curr : curr_reached)
        {
            reachable_states.insert(curr);
        }
    }
    return reachable_states;
}

std::set<std::shared_ptr<nfa_state>> e_closure(const std::set<std::shared_ptr<nfa_state>> nfa_states)
{
    std::set<std::shared_ptr<nfa_state>> reachable_states = nfa_states;
    std::stack<std::shared_ptr<nfa_state>> nfa_states_stack;
    std::map<state_id, bool> visited;
    for (const auto &state : nfa_states)
    {
        nfa_states_stack.push(state);
        visited[state->get_id()] = true;
    }
    while (!nfa_states_stack.empty())
    {
        auto curr_nfa_state = static_cast<std::shared_ptr<nfa_state> &&>(nfa_states_stack.top());
        nfa_states_stack.pop();
        auto trans_map = curr_nfa_state->get_transitions();
        std::vector<std::shared_ptr<nfa_state>> vec = trans_map[EPSILON];
        for (const auto &curr : vec)
        {
            if (!visited[curr->get_id()])
            {
                visited[curr->get_id()] = true;
                reachable_states.insert(curr);
                nfa_states_stack.push(curr);
            }
        }
    }
    return reachable_states;
}

std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr) {
    // Constructing all possible alphabet.

    char_set aa, bb;
    aa.add_character('a');
    bb.add_character('b');


    std::shared_ptr<dfa> dfa_ptr(new dfa());
    std::set<std::shared_ptr<nfa_state>> vec;
    vec.insert((std::shared_ptr<nfa_state> &&) nfa_ptr->get_start_state());
    std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(e_closure(vec),
                                                              static_cast<state_id>(dfa_ptr->get_total_states())));
    dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
    dfa_ptr->set_start_state(init_dfa_state);

    dfa_ptr->add_state(init_dfa_state);
    std::shared_ptr<dfa_state> curr_state;
    /*while ((curr_state = dfa_ptr->get_unmarked_state()) != nullptr) // get_next_state returns next unmarked state or null if no more unmarked states in dfa_ptr.
    {
        curr_state->set_marked(true);
        std::cout << "Current State = " << curr_state->get_id() << std::endl;
        for (auto curr : curr_state->get_composing_nfa_states()) {
            std::cout << curr->get_id() << " ";
        }
        std::cout << std::endl;
        for (const auto &inp : inputs)
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(), inp)),
                                    static_cast<state_id>(dfa_ptr->get_total_states())));
            if (new_state->equals(curr_state))
            {
                curr_state->insert_state(inp.name, curr_state);
                continue;
            }
            std::cout << "New State = " << new_state->get_id() << std::endl;
            for (auto curr : new_state->get_composing_nfa_states()) {
                std::cout << curr->get_id() << " ";
            }
            std::cout << std::endl;
            if (!dfa_ptr->contains(new_state))
            {
                dfa_ptr->add_state(new_state);
                dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
            }
            else
            {
                auto existing_states = dfa_ptr->get_dfa_states();
                for (auto st : existing_states)
                {
                    if (st->equals(new_state))
                    {
                        new_state = st;
                        break;
                    }
                }
            }
            curr_state->insert_state(inp.name, new_state);
            if (new_state->get_type() == ACCEPTANCE)
            {
                dfa_ptr->add_acceptance_state(new_state);
            }
        }
    }*/
    return dfa_ptr;
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
    nfa1->unify(nfa2);
    //nfa1->concat(nfa1);

    return nfa1;
}

std::shared_ptr<nfa> build_nfa3()
{
  char_set a_char_set = char_set();
  a_char_set.add_character ('a');


  char_set b_char_set = char_set();
  b_char_set.add_character ('b');

  std::shared_ptr <nfa> nfa_a1_ptr (new nfa(a_char_set));
  std::shared_ptr <nfa> nfa_a2_ptr (new nfa(a_char_set));
  std::shared_ptr<nfa> nfa_b1_ptr(new nfa(b_char_set));
  std::shared_ptr<nfa> nfa_b2_ptr(new nfa(b_char_set));
  std::shared_ptr<nfa> nfa_b3_ptr(new nfa(b_char_set));
  nfa_a1_ptr->unify(nfa_b1_ptr);
  nfa_a1_ptr->star();
  nfa_a1_ptr->concat(nfa_a2_ptr);
  nfa_a1_ptr->concat(nfa_b2_ptr);
  nfa_a1_ptr->concat(nfa_b3_ptr);

  return nfa_a1_ptr;
}

int main(int argc, char** argv) {
    //std::shared_ptr<nfa> my_nfa = build_nfa3();
    /*std::shared_ptr<nfa> my_nfa = build_nfa3();
    my_nfa->visualize();*/
    regular_expression regex = {"letter", "a-z"};
    std::map <std::string,std::shared_ptr<nfa>> sym_table;
    std::shared_ptr<nfa> my_nfa = evaluate_regex (regex, sym_table);
    if (my_nfa != nullptr)
      my_nfa->visualize();
  /*  std::shared_ptr<dfa> my_dfa = convert_nfa_dfa(my_nfa);
    std::cout << my_dfa->get_total_states();
    my_dfa->visualize();*/
//    draw_trans_table(my_dfa);
    return 0;
}
