//
// Created by awalid on 3/21/18.
//

#include <iostream>
#include <utility>
#include "nfa.h"
#include "nfa_state.h"

nfa::nfa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
        : fa(start_state, acceptance_states, total_states) {
    nfa::start_state = start_state;
    nfa::acceptance_states = acceptance_states;
    nfa::total_states = total_states;
}

void nfa::dfs (std::shared_ptr<state> curr_state, std::vector<bool> &visited, std::shared_ptr<std::ofstream> vis)
{
    visited[curr_state->get_id()] = true;

    std::map<std::string, std::vector<std::shared_ptr<nfa_state>>> transitions
            = std::static_pointer_cast<nfa_state>(curr_state)->get_transitions();

//    std::cout << "Current state = " << curr_state->get_id() << "\n";
//    for (auto trans : transitions) {
//        std::cout << "Key = " << trans.first << ", Destinations: ";
//        for (auto curr : trans.second)
//        {
//            std::cout << curr->get_id() << " ";
//        }
//        std::cout << "\n";
//    }
//    std::cout << "\n";

    for (auto edge : transitions)
    {
        std::string label = edge.first;
        std::vector<std::shared_ptr<nfa_state>> next_states = edge.second;
        for (auto state : next_states)
        {
            // Visualize
            if (vis != nullptr) {
                if (label.empty()) {
                    label = "ϵ";
                }
                *vis << curr_state->get_id() << " -> " << state->get_id() << " [ label = \"" << label << "\" ];\n";
            }
            if (!visited[state->get_id()]) {
                dfs(state, visited, vis);
            }
        }
    }
}


void nfa::unify(std::shared_ptr<nfa> nfa2)
{
    std::vector<regular_definition> v;
    regular_definition eps;
    char_set empty_char_set;

    eps.name = "eps";
    eps.sequence = empty_char_set;

    v.push_back(eps);

    std::shared_ptr<nfa_state> new_start_state = std::make_shared<nfa_state>(nfa_state (0, START, v));
    std::shared_ptr<nfa_state> new_acceptance_state = std::make_shared<nfa_state>(nfa_state (5, ACCEPTANCE, v));

    std::shared_ptr<nfa_state> old_start_state2 = std::static_pointer_cast<nfa_state>(nfa2->get_start_state());
    std::shared_ptr<nfa_state> old_start_state1 = std::static_pointer_cast<nfa_state>(start_state);

    old_start_state1->set_type(INTERMEDIATE);
    old_start_state2->set_type(INTERMEDIATE);

    new_start_state->insert_state(EPSILON, old_start_state1);
    new_start_state->insert_state(EPSILON, old_start_state2);

    
    std::shared_ptr<nfa_state> old_acceptance_state2 = std::static_pointer_cast<nfa_state>(nfa2->get_acceptance_states().front());
    std::shared_ptr<nfa_state> old_acceptance_state1 = std::static_pointer_cast<nfa_state>(acceptance_states.front());

    old_acceptance_state2->set_type(INTERMEDIATE);
    old_acceptance_state1->set_type(INTERMEDIATE);

    old_acceptance_state1->insert_state(EPSILON, new_acceptance_state);
    old_acceptance_state2->insert_state(EPSILON, new_acceptance_state);

    start_state = new_start_state;
    
    acceptance_states.clear();
    acceptance_states.push_back(new_acceptance_state);
}

void nfa::concat(std::shared_ptr<nfa> nfa2)
{
    acceptance_states.front()->insert_state(EPSILON, nfa2->get_start_state());
      
    nfa2->get_start_state()->set_type(INTERMEDIATE);
    get_acceptance_states().front()->set_type(INTERMEDIATE);
  
    acceptance_states.clear();
    acceptance_states.push_back(nfa2->get_acceptance_states().front());
}

void nfa::plus()
{
    std::shared_ptr<nfa> nfa2(new nfa(*this));
    nfa2->star();
    concat(nfa2);
}

void nfa::star()
{
    start_state->insert_state(EPSILON, acceptance_states.front());
    acceptance_states.front()->insert_state(EPSILON, start_state);
}


