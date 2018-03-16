#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <stack>

#include "state.h"
#include "transition_tabel.h"

class FA
{
private:
	State start_state;
 	State current_state;
  	std::vector <char> inputs;

public:
  FA (State start_state);

  virtual void visit_next_state (std::stack<State> &dfs_stack) = 0;

  Transition_Table get_transition_table ();
  void insert_state (char, State);
  State get_next_state (char input);
};

class DFA: public FA
{
public:
    DFA(const State &start_state);

private:
  DFA_State start_state;
  DFA_State current_state;

};

class NFA: public FA
{
public:
	NFA(const State &start_state);
private:
	NFA_State start_state;
	NFA_State current_state;
};

#endif // FINITE_AUTOMATA_H
