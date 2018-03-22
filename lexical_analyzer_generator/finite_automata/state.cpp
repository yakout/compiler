#include "state.h"

state::state (state_id id, state_type type,
   std::vector<regular_definition> defs)
{
    this->id = id;
    this->type = type;
    this->definitions = defs;
}

state::state(const state& s)
        : id(s.get_id()), type(s.get_type()), definitions(s.get_definitions())
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

const std::vector<regular_definition> &state::get_definitions() const {
    return definitions;
}


void state::set_type(state_type new_type) {
    type = new_type;
}

void state::set_id(state_id new_id) {
    id = new_id;
}



