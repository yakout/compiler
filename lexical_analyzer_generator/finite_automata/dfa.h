#ifndef DFA_H
#define DFA_H


#include "finite_automata.h"
#include "dfa_state.h"

class dfa : public fa {
public:
    explicit dfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    dfa();
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis, bool) override;
    void add_state(std::shared_ptr<dfa_state> s);
    const std::vector<std::shared_ptr<dfa_state>> &get_dfa_states() const;
    std::shared_ptr<dfa_state> get_unmarked_state();
    bool contains(std::shared_ptr<dfa_state> s);

private:
    std::vector<std::shared_ptr<dfa_state>> dfa_states;
};


#endif // DFA_H
