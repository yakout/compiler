//
// Created by awalid on 3/26/18.
//

#include <set>
#include "../nfa_state.h"
#include "../dfa_state.h"

#ifndef COMPILER_UTIL_H
#define COMPILER_UTIL_H

namespace util
{
    std::set<std::shared_ptr<nfa_state>> e_closure(std::set<std::shared_ptr<nfa_state>> nfa_states);
    std::set<std::shared_ptr<nfa_state>> move(std::set<std::shared_ptr<nfa_state>> nfa_states, char inp);
    std::set<std::shared_ptr<nfa_state>> move(std::set<std::shared_ptr<nfa_state>> nfa_states, std::string inp);
    std::set<std::set<std::shared_ptr<dfa_state>>> make_partition(std::set<std::set<std::shared_ptr<dfa_state>>> partition,
                   const std::shared_ptr<char_set> &alphabet);
}

#endif //COMPILER_UTIL_H
