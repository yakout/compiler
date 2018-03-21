//
// Created by awalid on 3/21/18.
//

#include "dfa_state.h"

dfa_state::dfa_state (int id, state_type type,
                      std::vector<regular_definition> definitions)
        : state (id, type, definitions)
{

}

void dfa_state::insert_state (std::string input, std::shared_ptr<state> const& state)
{
    transitions[input] = std::static_pointer_cast<dfa_state>(state);
}

std::shared_ptr<dfa_state> dfa_state::get_next_state (char input)
{

}

std::map<std::string, std::shared_ptr<dfa_state>> dfa_state::get_transitions()
{
    return transitions;
}