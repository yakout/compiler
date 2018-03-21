//
// Created by awalid on 3/21/18.
//

#ifndef JAVA_COMPILER_DFA_H
#define JAVA_COMPILER_DFA_H


#include "finite_automata.h"

class dfa : public fa {
public:
    explicit dfa(std::shared_ptr<state> start_state, std::shared_ptr<state> acceptance_state);
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis) override;
};


#endif //JAVA_COMPILER_DFA_H
