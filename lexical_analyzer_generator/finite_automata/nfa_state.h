//
// Created by awalid on 3/21/18.
//

#ifndef COMPILER_NFA_STATE_H
#define COMPILER_NFA_STATE_H


#include "state.h"

class nfa_state : public state {
private:
    std::map <std::string, std::vector<std::shared_ptr<nfa_state>>> transitions;
public:
    nfa_state (int id, state_type type, std::vector<regular_definition> definitions);
    void insert_state (std::string input, std::shared_ptr<state> const& state) override;
    std::vector<std::shared_ptr<nfa_state>> get_next_state (char input);
    std::map <std::string, std::vector<std::shared_ptr<nfa_state>>> get_transitions();
};


#endif //COMPILER_NFA_STATE_H
