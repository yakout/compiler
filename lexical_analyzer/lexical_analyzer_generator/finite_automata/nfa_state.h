#ifndef NFA_STATE_H
#define NFA_STATE_H


#include "state.h"

class nfa_state : public state {
private:
    std::map <std::string, std::vector<std::shared_ptr<nfa_state>>> transitions;
public:
    nfa_state (int id, state_type type, std::shared_ptr<char_set> st_ip);
    nfa_state (const nfa_state&);
    void insert_transition (std::string input, std::shared_ptr<state> const& state) override;
    std::shared_ptr<state> copy() override;

    // getters
    std::vector<std::shared_ptr<nfa_state>> get_next_state (char input);
    std::vector<std::shared_ptr<nfa_state>> get_next_state (std::string input);
    const std::map <std::string, std::vector<std::shared_ptr<nfa_state>>>& get_transitions() const;
};


#endif // NFA_STATE_H
