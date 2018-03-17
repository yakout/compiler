#include "state.h"

State::State (int id, state_type type)
{
    this->s_id = id;
    this->type = type;
}

NFA_State::NFA_State (int id, state_type type) : State (id, type)
{

}


DFA_State::DFA_State (int id, state_type type) : State (id, type)
{

}
