#include "state.h"

state::state (state_id id, state_type type, char_set st_ip)
{
    this->id = id;
    this->type = type;
    this->state_input = st_ip;
}

state::state(const state& s)
        : id(s.get_id()), type(s.get_type())
{

}

const state_id& state::get_id() const
{
    return id;
}

const state_type& state::get_type() const
{
    return type;
}



void state::set_type(state_type new_type) {
    type = new_type;
}

void state::set_id(state_id new_id) {
    id = new_id;
}
