//
// Created by awalid on 3/21/18.
//

#include "dfa.h"
#include "dfa_state.h"

#include <utility>

dfa::dfa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
        : fa(start_state, acceptance_states, total_states) {
    dfa::start_state = start_state;
    dfa::acceptance_states = acceptance_states;
    dfa::total_states = total_states;
}

dfa::dfa()
{
    dfa::total_states = 0;
}

/// TODO: Re-check this!
void dfa::dfs(std::shared_ptr<state> curr_state, std::vector<bool> &visited, std::shared_ptr<std::ofstream> vis) {
    visited[curr_state->get_id()] = true;

    std::map<std::string, std::shared_ptr<dfa_state>> transitions
            = std::static_pointer_cast<dfa_state>(curr_state)->get_transitions();

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
        std::shared_ptr<dfa_state> next_state = edge.second;

        // Visualize
        if (vis != nullptr) {
            if (label.empty()) {
                label = "ϵ";
            }
            *vis << curr_state->get_id() << " -> " << next_state->get_id() << " [ label = \"" << label << "\" ];\n";
        }
        if (!visited[next_state->get_id()]) {
            dfs(next_state, visited, vis);
        }
    }
}

void dfa::add_state(std::shared_ptr<dfa_state> s) {
    dfa::dfa_states.push_back(s);
}

const std::vector<std::shared_ptr<dfa_state>> &dfa::get_dfa_states() const {
    return dfa_states;
}

std::shared_ptr<dfa_state> dfa::get_unmarked_state() {
    for (auto curr_state : dfa::dfa_states)
    {
        if (!curr_state->is_marked())
        {
            return curr_state;
        }
    }
    return nullptr;
}

