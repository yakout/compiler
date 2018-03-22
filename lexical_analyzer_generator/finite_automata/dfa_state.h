//
// Created by awalid on 3/21/18.
//

#ifndef COMPILER_DFA_STATE_H
#define COMPILER_DFA_STATE_H

#include "state.h"
#include "nfa_state.h"

class dfa_state : public state {
private:
    std::map <std::string, std::shared_ptr<dfa_state>> transitions;
    std::vector<std::shared_ptr<nfa_state>> composing_nfa_states;
    bool marked;
public:
    bool is_marked() const;

    void set_marked(bool marked);

public:
    dfa_state (int id, state_type type, std::vector<regular_definition> definitions);
    explicit dfa_state(std::vector<std::shared_ptr<nfa_state>> nfa_states, state_id id);

    void insert_state (std::string input, std::shared_ptr<state> const& state) override;
    std::shared_ptr<dfa_state> get_next_state (char input);
    std::map <std::string, std::shared_ptr<dfa_state>> get_transitions();
    const std::vector<std::shared_ptr<nfa_state>> &get_composing_nfa_states() const;
};


#endif //COMPILER_DFA_STATE_H
