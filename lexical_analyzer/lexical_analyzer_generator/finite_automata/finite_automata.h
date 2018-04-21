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
	int max_id;

public:
	explicit fa(std::shared_ptr<state> start_state,
				std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
	fa(const fa&);
	fa();

    virtual void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
    	std::shared_ptr<std::ofstream> vis, bool update_acceptance_states,
    	 std::shared_ptr<char_set> alphabet) = 0;
	void visualize();

    /**
     * This function traverse the graph using dfs(,,,update_states = true)
     * and updates the acceptance states vector.
     */
	void update_acceptance_states();

	// getters
	int get_total_states() const;
	const std::vector<std::shared_ptr<state>> &get_acceptance_states() const;
	const std::shared_ptr<state> &get_start_state() const;
    int get_max_id();
	/**
	 * @brief returns the alphabet of the nfa.
	 * @details returns set of all intpu characters to states in nfa.
	 * @return char_set of all characters and ranges.
	 */
	// setters
	void set_start_state(std::shared_ptr<state>);
	void set_acceptance_states(std::vector<std::shared_ptr<state>>);
	void add_acceptance_state(std::shared_ptr<state>);
	void set_total_states(int total_states);
	void set_acceptance_states_priority(int);
	void set_acceptance_states_token_class(std::string);
};


#endif // FINITE_AUTOMATA_H
