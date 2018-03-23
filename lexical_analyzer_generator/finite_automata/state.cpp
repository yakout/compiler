#include "state.h"

#include <utility>

state::state (state_id _id, state_type _type, std::shared_ptr<char_set> st_ip)
        : id(_id), type(_type), state_input(std::move(st_ip))
{

}

state::state() {

}

state::state(const state& s)
        : id(s.get_id()), type(s.get_type()), state_input(s.get_char_set())
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

const std::shared_ptr<char_set> state::get_char_set() const
{
  return state_input;
}


void state::set_type(state_type new_type) {
    type = new_type;
}

void state::set_id(state_id new_id) {
    id = new_id;
}
