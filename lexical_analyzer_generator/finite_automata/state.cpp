#include "state.h"

State::State (int id, state_type type, regular_definition definition)
{
    this->s_id = id;
    this->type = type;
    this->definition = definition;
}

NFA_State::NFA_State (int id, state_type type,  regular_definition definition)
: State (id, type, definition)
{

}


DFA_State::DFA_State (int id, state_type type,  regular_definition definition)
: State (id, type, definition)
{

}

State* NFA_State::get_next_state (char input)
{

}

State* DFA_State::get_next_state (char input)
{

}
