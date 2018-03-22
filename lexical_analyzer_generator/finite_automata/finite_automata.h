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
	fa(const fa&);
	fa();
    virtual void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
					  std::shared_ptr<std::ofstream> vis, bool update_acceptance_states) = 0;
	void visualize();

    /**
     * this function traverse the graph using dfs(,,,update_states = true)
     * and updates the acceptance states vector.
     */
	void update_acceptance_states();

	// getters
	int get_total_states() const;
	const std::vector<std::shared_ptr<state>> &get_acceptance_states() const;
	const std::shared_ptr<state> &get_start_state() const;

	// setters
	void set_start_state(std::shared_ptr<state>);
	void set_acceptance_states(std::vector<std::shared_ptr<state>>);
};


#endif // FINITE_AUTOMATA_H
