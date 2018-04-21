#ifndef NFA_H
#define NFA_H


#include "finite_automata.h"
#include "nfa_state.h"

class nfa : public fa {
public:
    explicit nfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    explicit nfa(std::shared_ptr<char_set> st_ip, int id1, int id2);
    explicit nfa(std::shared_ptr<char_set> c_s);
    nfa();
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis, bool update_acceptance_states,
              std::shared_ptr<char_set> alphabet) override;
    void unify(std::shared_ptr<nfa>, bool unifiy_acceptance_states = true);
    void concat(std::shared_ptr<nfa>);
    void plus();
    void star();

    std::shared_ptr<nfa> copy();
    void renamify(state_id starting_id);
    static std::shared_ptr<char_set> build_epsilon_transition();

    std::shared_ptr<char_set> get_alphabet();
};


#endif // NFA_H
