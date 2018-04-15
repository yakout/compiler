#ifndef DFA_H
#define DFA_H


#include "finite_automata.h"
#include "dfa_state.h"
#include "nfa.h"


class dfa : public fa {
public:
    explicit dfa(std::shared_ptr<state> start_state,
        std::vector<std::shared_ptr<state>> acceptance_states, int total_states);
    dfa();
    explicit dfa(std::shared_ptr<nfa> combined_nfa);
    void dfs (std::shared_ptr<state> state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis, bool, std::shared_ptr<char_set>) override;

    void add_state(std::shared_ptr<dfa_state> s);
    const std::vector<std::shared_ptr<dfa_state>> &get_dfa_states() const;
    std::shared_ptr<dfa_state> get_unmarked_state();
    bool contains(std::shared_ptr<dfa_state> s);
    const std::shared_ptr<char_set> &get_alphabet() const;
    void set_alphabet(const std::shared_ptr<char_set> &alphabet);
    std::shared_ptr<dfa> minimize();
    void draw_trans_table();

private:
    std::vector<std::shared_ptr<dfa_state>> dfa_states;
    std::shared_ptr<char_set> alphabet;
};


#endif // DFA_H
