//
// Created by awalid on 3/26/18.
//

#include <set>
#include <stack>
#include "../nfa_state.h"
#include "../dfa_state.h"

bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
                const std::string &inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition)
{
    auto dest_state_1 = s1->get_next_state(inp);
    auto dest_state_2 = s2->get_next_state(inp);
    if (dest_state_1 == nullptr && dest_state_2 == nullptr) {
        return true;
    }
    if (dest_state_1 == nullptr || dest_state_2 == nullptr) {
        return false;
    }
    for (auto grp : partition)
    {
        bool found_s1, found_s2;
        found_s1 = found_s2 = false;
        for (const auto &state : grp)
        {
            if (state->get_id() == dest_state_1->get_id())
                found_s1 = true;
            if (state->get_id() == dest_state_2->get_id())
                found_s2 = true;
        }
        if (found_s1 && found_s2)
            return true;
    }
    return false;
}

bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
                const char inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition)
{
    auto dest_state_1 = s1->get_next_state(inp);
    auto dest_state_2 = s2->get_next_state(inp);
    if (dest_state_1 == nullptr && dest_state_2 == nullptr) {
        return true;
    }
    if (dest_state_1 == nullptr || dest_state_2 == nullptr) {
        return false;
    }
    for (auto grp : partition)
    {
        bool found_s1, found_s2;
        found_s1 = found_s2 = false;
        for (const auto &state : grp)
        {
            if (state->get_id() == dest_state_1->get_id())
                found_s1 = true;
            if (state->get_id() == dest_state_2->get_id())
                found_s2 = true;
        }
        if (found_s1 && found_s2)
            return true;
    }
    return false;
}

namespace util
{
    std::set<std::shared_ptr<nfa_state>> e_closure(const std::set<std::shared_ptr<nfa_state>> nfa_states)
    {
        std::set<std::shared_ptr<nfa_state>> reachable_states = nfa_states;
        std::stack<std::shared_ptr<nfa_state>> nfa_states_stack;
        std::map<state_id, bool> visited;
        for (const auto &state : nfa_states)
        {
            nfa_states_stack.push(state);
            visited[state->get_id()] = true;
        }
        while (!nfa_states_stack.empty())
        {
            auto curr_nfa_state = static_cast<std::shared_ptr<nfa_state> &&>(nfa_states_stack.top());
            nfa_states_stack.pop();
            std::vector<std::shared_ptr<nfa_state>> vec = curr_nfa_state->get_next_state('\0');
            for (const auto &curr : vec)
            {
                if (!visited[curr->get_id()])
                {
                    visited[curr->get_id()] = true;
                    reachable_states.insert(curr);
                    nfa_states_stack.push(curr);
                }
            }
        }
        return reachable_states;
    }

    std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> nfa_states, char inp) {
        std::set<std::shared_ptr<nfa_state>> reachable_states;
        for (const auto &state : nfa_states)
        {
            std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_next_state(inp);
            for (const auto &curr : curr_reached)
            {
                reachable_states.insert(curr);
            }
        }
        return reachable_states;
    }

    std::set<std::shared_ptr<nfa_state>> move(std::set<std::shared_ptr<nfa_state>> nfa_states, std::string inp)
    {
        std::set<std::shared_ptr<nfa_state>> reachable_states;
        for (const auto &state : nfa_states)
        {
            std::vector<std::shared_ptr<nfa_state>> curr_reached = state->get_next_state(inp);
            for (const auto &curr : curr_reached)
            {
                reachable_states.insert(curr);
            }
        }
        return reachable_states;
    }

    std::set<std::set<std::shared_ptr<dfa_state>>>
    make_partition(std::set<std::set<std::shared_ptr<dfa_state>>> partition,
                   const std::shared_ptr<char_set> &alphabet)
    {
        std::set<std::set<std::shared_ptr<dfa_state>>> new_partition;
        std::map<int, bool> partitioned;
        for (auto group : partition)
        {
            for (const auto &state : group)
            {
                if (partitioned[state->get_id()])
                {
                    continue;
                }
                std::set<std::shared_ptr<dfa_state>> new_group;
                new_group.insert(state);
                partitioned[state->get_id()] = true;
                for (const auto &s : group)
                {
                    if (!partitioned[s->get_id()])
                    {
                        bool same_grp = true;
                        for (auto inp : alphabet->get_characters())
                        {
                            if (!same_group(state, s, inp.first, partition))
                            {
                                same_grp = false;
                                break;
                            }
                        }
                        if (same_grp)
                        {
                            for (const auto &range : alphabet->get_ranges())
                            {
                                if (!same_group(state, s, range->get_range_string(), partition))
                                {
                                    same_grp = false;
                                    break;
                                }
                            }
                        }
                        if (same_grp && state->get_token_class() == s->get_token_class())
                        {
                            new_group.insert(s);
                            partitioned[s->get_id()] = true;
                        }
                    }
                }
                new_partition.insert(new_group);
            }
        }
        return new_partition;
    }
}




