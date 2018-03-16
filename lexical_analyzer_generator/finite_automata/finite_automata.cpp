#include "finite_automata.h"

NFA::NFA(const State &start_state) : FA(start_state) {}

DFA::DFA(const State &start_state) : FA(start_state) {}

Transition_Table FA::get_transition_table() {
    return Transition_Table();
}

void FA::insert_state(char, State) {

}

State FA::get_next_state(char input) {
    return State(0, INTERMEDIATE);
}

