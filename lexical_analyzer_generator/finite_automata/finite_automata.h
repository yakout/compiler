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
	std::shared_ptr<state> acceptance_state;

public:
	explicit fa(std::shared_ptr<state> start_state, std::shared_ptr<state> acceptance_state);
    virtual void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
					  std::shared_ptr<std::ofstream> vis) = 0;
	void visualize();
};


#endif // FINITE_AUTOMATA_H
