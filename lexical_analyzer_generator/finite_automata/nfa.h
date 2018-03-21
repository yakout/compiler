//
// Created by awalid on 3/21/18.
//

#ifndef JAVA_COMPILER_NFA_H
#define JAVA_COMPILER_NFA_H


#include "finite_automata.h"
#include "nfa_state.h"

class nfa : public fa {
public:
    explicit nfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis) override;
    void unify(std::shared_ptr<nfa>);
    void concat(std::shared_ptr<nfa>);
    void plus();
    void star();
};


#endif //JAVA_COMPILER_NFA_H
