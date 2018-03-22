#ifndef DFA_H
#define DFA_H


#include "finite_automata.h"

class dfa : public fa {
public:
    explicit dfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis) override;
};


#endif // DFA_H
