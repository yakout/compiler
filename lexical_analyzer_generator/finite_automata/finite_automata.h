#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <stack>

#include "state.h"
#include "transition_table.h"

class FA
{
protected:
	std::shared_ptr<State> start_state;
	std::shared_ptr<State> current_state;

public:
	explicit FA(State &start_state);

  virtual void visit_next_state (std::stack<State> &dfs_stack) = 0;
	virtual std::shared_ptr<State> get_next_state (char input) = 0;

	Transition_Table get_transition_table ();
};

class DFA: public FA
{
public:
	explicit DFA(State &start_state);
	void visit_next_state (std::stack<State> &dfs_stack) override;
	std::shared_ptr<State> get_next_state (char input) override;
};

class NFA: public FA
{
public:
	explicit NFA(State &start_state);
	void visit_next_state (std::stack<State> &dfs_stack) override;
	std::shared_ptr<State> get_next_state (char input) override;
};

#endif // FINITE_AUTOMATA_H
