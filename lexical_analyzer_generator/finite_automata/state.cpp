#include "state.h"

State::State (int id, state_type type,
   std::vector<regular_definition> definitions)
{
    this->s_id = id;
    this->type = type;
    this->definitions = definitions;
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

State* NFA_State::get_next_state (char input)
{

}

State* DFA_State::get_next_state (char input)
{

}
