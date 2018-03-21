//
// Created by awalid on 3/21/18.
//

#include <iostream>
#include <utility>
#include "nfa.h"
#include "nfa_state.h"

nfa::nfa (std::shared_ptr<state> start_state, std::shared_ptr<state> acceptance_state)
        : fa(start_state, acceptance_state)
{

}

void nfa::dfs (std::shared_ptr<state> curr_state, std::vector<bool> &visited, std::shared_ptr<std::ofstream> vis)
{
//    visited[curr_state->get_id()] = true;

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
            std::cout << state->get_id() << std::endl;
            if (!visited[state->get_id()]) {
                // Plot
                if (vis != nullptr) {
                    if (label.empty()) {
                        label = "E";
                    }
                    *vis << curr_state->get_id() << " -> " << state->get_id() << " [ label = \"" << label << "\" ];\n";
                }
                dfs(state, visited, vis);
            }
        }
    }
}