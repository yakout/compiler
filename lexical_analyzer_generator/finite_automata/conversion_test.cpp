//
// Created by awalid on 3/21/18.
//

#include <memory>
#include <queue>
#include <iostream>
#include "finite_automata.h"
#include "state.h"
#include "nfa.h"
#include "dfa.h"
#include "nfa_state.h"
#include "dfa_state.h"

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

std::vector<std::shared_ptr<nfa_state>> move(const std::vector<std::shared_ptr<nfa_state>> &nfa_states,
                                              regular_definition inp)
{
    std::vector<std::shared_ptr<nfa_state>> reachable_states;
    for (const auto &state : nfa_states)
    {
        std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_transitions()[inp.name];
        for (const auto &curr : curr_reached)
        {
            reachable_states.push_back(curr);
        }
    }
    return reachable_states;
}

std::vector<std::shared_ptr<nfa_state>> e_closure(const std::vector<std::shared_ptr<nfa_state>> nfa_states)
{
    std::vector<std::shared_ptr<nfa_state>> reachable_states = nfa_states;
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
        std::vector<std::shared_ptr<nfa_state>> vec = curr_nfa_state->get_transitions()[EPSILON];
        for (const auto &curr : vec)
        {
            if (!visited[curr->get_id()])
            {
                visited[curr->get_id()] = true;
                reachable_states.push_back(curr);
                nfa_states_stack.push(curr);
            }
        }
    }
    return reachable_states;
}

std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr) {
    // Constructing all possible alphabet.
    std::vector<regular_definition> inputs;
    regular_definition a, b;
    char_set aa, bb;
    aa.add_character('a');
    bb.add_character('b');
    a.name = "a";
    a.sequence = aa;
    b.name = "b";
    b.sequence = bb;
    inputs.push_back(a);
    inputs.push_back(b);


    std::shared_ptr<dfa> dfa_ptr(new dfa());
    std::vector<std::shared_ptr<nfa_state>> vec;
    vec.push_back((std::shared_ptr<nfa_state> &&) nfa_ptr->get_start_state());
    std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(e_closure(vec),
                                                              static_cast<state_id>(dfa_ptr->get_total_states())));
    dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
    dfa_ptr->set_start_state(init_dfa_state);
    std::queue<std::shared_ptr<dfa_state>> q;
    std::map<state_id, bool> visited;
    q.push((std::shared_ptr<dfa_state> &&) dfa_ptr->get_start_state()); // SEG FAULT HERE.
    std::cout << dfa_ptr->get_start_state()->get_id() << "\n";
    visited[dfa_ptr->get_start_state()->get_id()] = true;
    while (!q.empty())
    {
        auto curr_state = static_cast<std::shared_ptr<dfa_state> &&>(q.front());
        q.pop();
        for (const auto &inp : inputs)
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(), inp)),
                                    static_cast<state_id>(dfa_ptr->get_total_states())));
            dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
            if (!visited[new_state->get_id()])
            {
                visited[new_state->get_id()] = true;
                q.push(new_state);
            }
            curr_state->insert_state(inp.name, new_state);
            if (new_state->get_type() == ACCEPTANCE)
            {
                dfa_ptr->add_acceptance_state(new_state);
            }
        }
    }
    return dfa_ptr;
}

int main(int argc, char** argv) {
    std::shared_ptr<nfa> my_nfa = build_nfa();
    my_nfa->visualize();
    std::shared_ptr<dfa> my_dfa = convert_nfa_dfa(my_nfa);
//    my_dfa->visualize(); // Would this work?
//    draw_trans_table(my_dfa);
    return 0;
}


