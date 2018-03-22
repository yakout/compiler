#ifndef DFA_STATE_H
#define DFA_STATE_H

#include "state.h"

class dfa_state : public state {
private:
    std::map <std::string, std::shared_ptr<dfa_state>> transitions;
public:
    dfa_state (int id, state_type type, char_set st_ip);
    void insert_transition (std::string input, std::shared_ptr<state> const& state) override;
    std::shared_ptr<dfa_state> get_next_state (char input);
    std::map <std::string, std::shared_ptr<dfa_state>> get_transitions();
};


#endif // DFA_STATE_H
