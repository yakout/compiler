#include "state.h"

state::state (int id, state_type type,
   std::vector<regular_definition> definitions)
{
    this->id = id;
    this->type = type;
    this->definitions = definitions;
}

state::state() {

}

state_id state::get_id() {
    return id;
}

state_type state::get_type() {
    return type;
}

void state::set_type(state_type new_type) {
    type = new_type;
}

