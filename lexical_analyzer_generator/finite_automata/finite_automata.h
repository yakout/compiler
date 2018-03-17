#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <stack>

#include "state.h"
#include "transition_tabel.h"

class FA
{
private:
	State* start_state;
 	State* current_state;
  std::vector <char> inputs;

public:
  FA (State &start_state);

  virtual void visit_next_state (std::stack<State> &dfs_stack) = 0;
	//virtual State* get_next_state (char input) = 0;

  Transition_Table get_transition_table ();
  void insert_state (char input, State &state);
};

class DFA: public FA
{
public:
    DFA(State &start_state);
		void visit_next_state (std::stack<State> &dfs_stack);
		//State* get_next_state (char input);
};

class NFA: public FA
{
public:
	NFA(State &start_state);
	void visit_next_state (std::stack<State> &dfs_stack);
	//State* get_next_state (char input);		
};

#endif // FINITE_AUTOMATA_H
