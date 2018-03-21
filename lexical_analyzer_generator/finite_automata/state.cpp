#include "state.h"

State::State (int id, state_type type,
   std::vector<regular_definition> definitions)
{
    this->id = id;
    this->type = type;
    this->definitions = definitions;
}

state_id State::get_id() {
    return id;
}

state_type State::get_type() {
    return type;
}

void NFA_State::insert_state (std::string input, std::shared_ptr<State> const& state)
{
	//if (transitions.count(input) == 0) {
        // input not in map
    //    std::vector<std::shared_ptr<NFA_State>> states;
    //    states.push_back(std::static_pointer_cast<NFA_State>(state));
	//	transitions[input] = states;
	//} else {
        // input in map
        transitions[input].push_back(std::static_pointer_cast<NFA_State>(state));
   // }

}

void DFA_State::insert_state (std::string input, std::shared_ptr<State> const& state)
{
	transitions[input] = std::static_pointer_cast<DFA_State>(state);
}

NFA_State::NFA_State (int id, state_type type,
   std::vector<regular_definition> definitions)
: State (id, type, definitions)
{

}


DFA_State::DFA_State (int id, state_type type,
    std::vector<regular_definition> definitions)
: State (id, type, definitions)
{

}

std::vector<std::shared_ptr<NFA_State>> NFA_State::get_next_state (char input)
{
    for (auto def : State::definitions) {
        std::string input_str = def.sequence.get_string(input);
        if (!input_str.empty()) {
            return transitions[input_str];
        }
    }
}

std::map<std::string, std::vector<std::shared_ptr<NFA_State>>> NFA_State::get_transitions()
{
    return transitions;
}


std::shared_ptr<DFA_State> DFA_State::get_next_state (char input)
{

}

std::map<std::string, std::shared_ptr<DFA_State>> DFA_State::get_transitions()
{
    return transitions;
}

