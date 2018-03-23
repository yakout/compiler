#include <iostream>
#include "nfa_state.h"

#include <utility>

nfa_state::nfa_state (int id, state_type type, std::shared_ptr<char_set> st_ip)
        : state (id, type, std::move(st_ip))
{

}

nfa_state::nfa_state(const nfa_state & s)
        : state::state(s), transitions()
{
    for (auto const& edge : s.get_transitions())
    {
        std::vector<std::shared_ptr<nfa_state>> v;
        for (auto const& next_state : edge.second)
        {
            v.push_back(std::static_pointer_cast<nfa_state>(next_state->copy()));
        }
        transitions[edge.first] = v;
    }
}

void nfa_state::insert_transition (std::string input, std::shared_ptr<state> const& state)
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

const std::map<std::string, std::vector<std::shared_ptr<nfa_state>>>&
nfa_state::get_transitions() const
{
    return transitions;
}

std::vector<std::shared_ptr<nfa_state>> nfa_state::get_next_state(char input)
{
    std::string key = state_input->get_string(input);
    if (key.empty() && input != '\0')
        return std::vector<std::shared_ptr<nfa_state>>();
    return transitions[key];
}

std::vector<std::shared_ptr<nfa_state>> nfa_state::get_next_state(std::string input) {
    return transitions[input];
}

std::shared_ptr<state> nfa_state::copy() {
    return std::make_shared<nfa_state>(*this);
}


