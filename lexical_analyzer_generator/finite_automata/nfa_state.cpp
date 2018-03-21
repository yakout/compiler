//
// Created by awalid on 3/21/18.
//

#include "nfa_state.h"

nfa_state::nfa_state (int id, state_type type,
                      std::vector<regular_definition> definitions)
        : state (id, type, definitions)
{

}

void nfa_state::insert_state (std::string input, std::shared_ptr<state> const& state)
{
    //if (transitions.count(input) == 0) {
    // input not in map
    //    std::vector<std::shared_ptr<nfa_state>> states;
    //    states.push_back(std::static_pointer_cast<nfa_state>(state));
    //	transitions[input] = states;
    //} else {
    // input in map
    transitions[input].push_back(std::static_pointer_cast<nfa_state>(state));
    // }

}

std::map<std::string, std::vector<std::shared_ptr<nfa_state>>> nfa_state::get_transitions()
{
    return transitions;
}

std::vector<std::shared_ptr<nfa_state>> nfa_state::get_next_state (char input)
{
    for (auto def : state::definitions) {
        std::string input_str = def.sequence.get_string(input);
        if (!input_str.empty()) {
            return transitions[input_str];
        }
    }
}