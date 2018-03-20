#include "finite_automata.h"

FA::FA (State &start_state)
{
}

NFA::NFA (State &start_state) : FA(start_state) {}

DFA::DFA (State &start_state) : FA(start_state) {}

Transition_Table FA::get_transition_table ()
{
    return Transition_Table();
}

void FA::insert_state (char input, State &state)
{

}

void NFA::visit_next_state (std::stack<State> &dfs_stack)
{

}

void DFA::visit_next_state (std::stack<State> &dfs_stack)
{

}

State* NFA::get_next_state (char input)
{
}

State* DFA::get_next_state (char input)
{
}
