#ifndef CONVERSION_TEST_H
#define CONVERSION_TEST_H


void draw_trans_table(std::shared_ptr<dfa> dfa);
std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const char inp);
std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const std::string &inp);
std::set<std::shared_ptr<nfa_state>> e_closure(const std::set<std::shared_ptr<nfa_state>> nfa_states);
std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr);
bool equal_partitions(std::set<std::set<std::shared_ptr<dfa_state>>> part1, std::set<std::set<std::shared_ptr<dfa_state>>> part2);
bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
                const std::string &inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition);
bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
                const char inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition);
std::set<std::set<std::shared_ptr<dfa_state>>>
make_partition(std::set<std::set<std::shared_ptr<dfa_state>>> partition,
               const std::shared_ptr<char_set> &alphabet);
std::shared_ptr<dfa> minimize(const std::shared_ptr<dfa> &dfa_ptr);

#endif // CONVERSION_TEST_H