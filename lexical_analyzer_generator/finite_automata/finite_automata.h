#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <stack>
#include <fstream>
#include <memory>

#include "state.h"
#include "transition_table.h"

class FA
{
protected:
	std::shared_ptr<State> start_state;
	std::shared_ptr<State> acceptance_state;

	std::shared_ptr<State> current_state;

public:
	explicit FA(std::shared_ptr<State> start_state, std::shared_ptr<State> acceptance_state);
    virtual void dfs (std::shared_ptr<State> state, std::vector<bool> visited, std::shared_ptr<std::ofstream> vis = nullptr) = 0;
    void visualize();
	Transition_Table get_transition_table ();
};

class DFA: public FA
{
public:
	explicit DFA(std::shared_ptr<State> start_state, std::shared_ptr<State> acceptance_state);
	void dfs (std::shared_ptr<State> state, std::vector<bool> visited, std::shared_ptr<std::ofstream> vis = nullptr) override;
};

class NFA: public FA
{
public:
	explicit NFA(std::shared_ptr<State> start_state, std::shared_ptr<State> acceptance_state);
	void dfs (std::shared_ptr<State> state, std::vector<bool> visited, std::shared_ptr<std::ofstream> vis = nullptr) override;
};

#endif // FINITE_AUTOMATA_H
