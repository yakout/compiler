#include "dfa.h"
#include "dfa_state.h"

#include <utility>

dfa::dfa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
        : fa(start_state, acceptance_states, total_states) {
    dfa::start_state = start_state;
    dfa::acceptance_states = acceptance_states;
    dfa::total_states = total_states;
}

/// TODO: Re-check this!
void dfa::dfs(std::shared_ptr<state> curr_state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis, bool update_acceptance_states) {
    visited[curr_state->get_id()] = true;
    if (update_acceptance_states && curr_state->get_type() == ACCEPTANCE)
    {
        acceptance_states.push_back(curr_state);
    }

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
            dfs(next_state, visited, vis, update_acceptance_states);
        }
    }
}

