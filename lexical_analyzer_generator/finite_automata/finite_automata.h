#ifndef FINITE_AUTOMATA_H
#define FINITE_AUTOMATA_H

#include <stack>
#include <fstream>
#include <memory>

#include "state.h"

class fa
{
protected:
	std::shared_ptr<state> start_state;
	std::vector<std::shared_ptr<state>> acceptance_states;
	int total_states;

public:
	explicit fa(std::shared_ptr<state> start_state,
				std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    virtual void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
					  std::shared_ptr<std::ofstream> vis) = 0;
	void visualize();

	const std::vector<std::shared_ptr<state>> &getAcceptance_states() const;
	int getTotal_states() const;
	const std::shared_ptr<state> &get_start_state() const;

};


#endif // FINITE_AUTOMATA_H
