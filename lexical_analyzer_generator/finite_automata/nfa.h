#ifndef NFA_H
#define NFA_H


#include "finite_automata.h"
#include "nfa_state.h"

class nfa : public fa {
public:
    explicit nfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    nfa(std::vector<regular_definition> defs, int id1, int id2);
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis) override;
    void unify(std::shared_ptr<nfa>);
    void concat(std::shared_ptr<nfa>);
    void plus();
    void star();

    static std::vector<regular_definition> build_epsilon_transition();
};


#endif // NFA_H
