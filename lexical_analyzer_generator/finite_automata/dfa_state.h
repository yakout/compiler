#ifndef DFA_STATE_H
#define DFA_STATE_H

#include "state.h"
#include "nfa_state.h"
#include <set>

class dfa_state : public state {
private:
    std::map <std::string, std::shared_ptr<dfa_state>> transitions;
    std::set<std::shared_ptr<nfa_state>> composing_nfa_states;
    bool marked;
    std::string token_class;

public:
    dfa_state (int, state_type, char_set, std::string = "");
    explicit dfa_state(std::set<std::shared_ptr<nfa_state>> nfa_states, state_id id);

    void insert_transition (std::string input, std::shared_ptr<state> const& state) override;
    std::shared_ptr<dfa_state> get_next_state (char input);
    std::map <std::string, std::shared_ptr<dfa_state>> get_transitions();
    const std::set<std::shared_ptr<nfa_state>> &get_composing_nfa_states() const;
    const std::string get_token_class () const;
    bool is_marked() const;
    void set_marked(bool marked);
    bool equals(std::shared_ptr<dfa_state> s);
    std::shared_ptr<state> copy() override;
};


#endif // DFA_STATE_H
