#include <iostream>
#include <memory>
#include <queue>
#include <iostream>
#include <set>
#include <climits>

#include "../../lexical_analyzer_generator/finite_automata/finite_automata.h"
#include "../../lexical_analyzer_generator/finite_automata/state.h"
#include "../../lexical_analyzer_generator/finite_automata/nfa.h"
#include "../../lexical_analyzer_generator/finite_automata/dfa.h"
#include "../../lexical_analyzer_generator/finite_automata/nfa_state.h"
#include "../../lexical_analyzer_generator/finite_automata/dfa_state.h"
#include "../../lexical_analyzer_generator/nfa_tools/regex_processor.h"
#include "../../lexical_analyzer_generator/lexical_analyzer_generator.h"

#define EPSILON ""

bool dead_state(const std::shared_ptr<dfa_state> &shared_ptr);

void draw_trans_table(std::shared_ptr<dfa> dfa)
{
    std::shared_ptr<std::ofstream> out_file(new std::ofstream());
    out_file->open("transition_table.txt");
    *out_file << "Total States: " << dfa->get_total_states() << "\n";
    *out_file << "Start State(s): {" << dfa->get_start_state()->get_id() << "}\n";
    *out_file << "Acceptance State(s): " << dfa->get_acceptance_states().size() << "\n";
    for (auto acc_state : dfa->get_acceptance_states())
    {
        *out_file << "{" << acc_state->get_id() << "}\t" << acc_state->get_token_class() << "\n";
    }
    *out_file << "State\t";
    std::set<char> alph_chars;
    std::set<std::string> alph_ranges;
    for (auto inp_char : dfa->get_alphabet()->get_characters())
    {
        alph_chars.insert(inp_char.first);
    }
    for (auto c : alph_chars) {
        *out_file << c << "\t";
    }
    for (auto inp_range : dfa->get_alphabet()->get_ranges())
    {
        alph_ranges.insert(inp_range->get_range_string());
    }
    for (auto range : alph_ranges) {
        *out_file << range << "\t";
    }
    *out_file << "\n";
    for (auto state : dfa->get_dfa_states())
    {
        *out_file << "{" << state->get_id() << "}\t";
        for (auto inp_char : dfa->get_alphabet()->get_characters())
        {
            auto target_state = state->get_next_state(inp_char.first);
            if (target_state == nullptr)
            {
                *out_file << "{-}\t";
            }
            else
            {
                *out_file << "{" << target_state->get_id() << "}\t";
            }
        }
        for (auto inp_range : dfa->get_alphabet()->get_ranges())
        {
            auto target_state = state->get_next_state(inp_range->get_range_string());
            if (target_state == nullptr)
            {
                *out_file << "{-}\t";
            }
            else
            {
                *out_file << "{" << target_state->get_id() << "}\t";
            }
        }
        *out_file << "\n";
    }
}

std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const char inp)
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

std::set<std::shared_ptr<nfa_state>> move(const std::set<std::shared_ptr<nfa_state>> &nfa_states, const std::string &inp)
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

std::shared_ptr<dfa> convert_nfa_dfa(const std::shared_ptr<nfa> &nfa_ptr) {
    std::shared_ptr<dfa> dfa_ptr(new dfa());
    dfa_ptr->set_alphabet(nfa_ptr->get_alphabet());
//    std::cout << "ALPHABET: ";
//    for (auto ch : dfa_ptr->get_alphabet()->get_characters()) {
//        std::cout << ch.first << " ";
//    }
//    for (auto x : dfa_ptr->get_alphabet()->get_ranges()) {
//        std::cout << x->get_range_string() << " ";
//    }
//    exit(0);
    std::set<std::shared_ptr<nfa_state>> vec;
    vec.insert((std::shared_ptr<nfa_state> &&) nfa_ptr->get_start_state());
    std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(e_closure(vec),
                                                              static_cast<state_id>(dfa_ptr->get_total_states())));
    dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
    dfa_ptr->set_start_state(init_dfa_state);
    dfa_ptr->add_state(init_dfa_state);

    std::shared_ptr<dfa_state> curr_state;
    while ((curr_state = dfa_ptr->get_unmarked_state()) != nullptr)
    {
        curr_state->set_marked(true);
        std::cout << "Current State = " << curr_state->get_id() << std::endl;
        for (auto curr : curr_state->get_composing_nfa_states()) {
            std::cout << curr->get_id() << " ";
        }
        std::cout << std::endl;
        for (const auto &curr_char : dfa_ptr->get_alphabet()->get_characters())
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(),
                                                                              curr_char.first)),
                                    static_cast<state_id>(dfa_ptr->get_total_states())));
            if (new_state->get_composing_nfa_states().empty()) { // dead state
                continue;
            }
            if (new_state->equals(curr_state))
            {
                curr_state->insert_transition(dfa_ptr->get_alphabet()->get_string(curr_char.first), curr_state);
                continue;
            }
            std::cout << "New State = " << new_state->get_id() << std::endl;
            for (auto curr : new_state->get_composing_nfa_states()) {
                std::cout << curr->get_id() << " ";
            }
            std::cout << std::endl;
            if (!dfa_ptr->contains(new_state))
            {
                dfa_ptr->add_state(new_state);
                dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
                if (new_state->get_type() == ACCEPTANCE)
                {
                    dfa_ptr->add_acceptance_state(new_state);
                    int max_pri = INT_MAX;
                    std::string token_class;
                    for (auto s : new_state->get_composing_nfa_states())
                    {
                        if (s->get_token_class_priority() < max_pri)
                        {
                            token_class = s->get_token_class();
                            max_pri = s->get_token_class_priority();
                        }
                    }
                    new_state->set_token_class(token_class);
                }
            }
            else
            {
                auto existing_states = dfa_ptr->get_dfa_states();
                for (auto st : existing_states)
                {
                    if (st->equals(new_state))
                    {
                        new_state = st;
                        break;
                    }
                }
            }
            curr_state->insert_transition(dfa_ptr->get_alphabet()->get_string(curr_char.first), new_state);
        }
        for (const auto &curr_range : dfa_ptr->get_alphabet()->get_ranges())
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(e_closure(move(curr_state->get_composing_nfa_states(),
                                                                              curr_range->get_range_string())),
                                                               static_cast<state_id>(dfa_ptr->get_total_states())));
            // dead state
            if (new_state->get_composing_nfa_states().empty()) { // dead state
                continue;
            }
            if (new_state->equals(curr_state))
            {
                curr_state->insert_transition(curr_range->get_range_string(), curr_state);
                continue;
            }
//            std::cout << "New State = " << new_state->get_id() << std::endl;
//            for (auto curr : new_state->get_composing_nfa_states()) {
//                std::cout << curr->get_id() << " ";
//            }
//            std::cout << std::endl;
            if (!dfa_ptr->contains(new_state))
            {
                dfa_ptr->add_state(new_state);
                dfa_ptr->set_total_states(dfa_ptr->get_total_states() + 1);
                if (new_state->get_type() == ACCEPTANCE)
                {
                    dfa_ptr->add_acceptance_state(new_state);
                    int max_pri = INT_MAX;
                    std::string token_class;
                    for (auto s : new_state->get_composing_nfa_states())
                    {
                        if (s->get_token_class_priority() < max_pri)
                        {
                            token_class = s->get_token_class();
                            max_pri = s->get_token_class_priority();
                        }
                    }
                    new_state->set_token_class(token_class);
                }
            }
            else
            {
                auto existing_states = dfa_ptr->get_dfa_states();
                for (auto st : existing_states)
                {
                    if (st->equals(new_state))
                    {
                        new_state = st;
                        break;
                    }
                }
            }
            curr_state->insert_transition(curr_range->get_range_string(), new_state);
        }
    }
    return dfa_ptr;
}

/// CHECK THIS AGAIN!
bool equal_partitions(std::set<std::set<std::shared_ptr<dfa_state>>> part1,
                      std::set<std::set<std::shared_ptr<dfa_state>>> part2) {
    return part1 == part2;
}
bool same_group(const std::shared_ptr<dfa_state> &s1, const std::shared_ptr<dfa_state> &s2,
                const std::string &inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition) {
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
                const char inp, std::set<std::set<std::shared_ptr<dfa_state>>> partition) {
    auto dest_state_1 = s1->get_next_state(inp);
    auto dest_state_2 = s2->get_next_state(inp);
    if (dest_state_1 == nullptr && dest_state_2 == nullptr) {
        return true;
    }
    if (dest_state_1 == nullptr || dest_state_2 == nullptr) {
        return false;
    }
//    std::cout << "Dest#1: " << dest_state_1->get_id() << ", Dest #2: " << dest_state_2->get_id() << "\n";
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

std::set<std::set<std::shared_ptr<dfa_state>>>
make_partition(std::set<std::set<std::shared_ptr<dfa_state>>> partition,
               const std::shared_ptr<char_set> &alphabet) {
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
//                std::cout << s->get_id() << "\n";
                if (!partitioned[s->get_id()])
                {
                    bool same_grp = true;
                    for (auto inp : alphabet->get_characters())
                    {
//                        std::cout << "----" << state->get_id() << "    " << s->get_id() << " input = " << inp.first << "\n";
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

std::shared_ptr<dfa> minimize(const std::shared_ptr<dfa> &dfa_ptr)
{
    // FIRST OF ALL MAKE A PARTITION OF ACC AND NON-ACC STATES
    std::set<std::set<std::shared_ptr<dfa_state>>> partition;
    std::set<std::shared_ptr<dfa_state>> non_acc_states, acc_states;
    for (const auto &s : dfa_ptr->get_dfa_states())
    {
        if (s->get_type() != ACCEPTANCE)
        {
            non_acc_states.insert(s);
        }
        else
        {
            acc_states.insert(s);
        }
    }
    partition.insert(acc_states);
    partition.insert(non_acc_states);

    // SECONDLY: PARTITION CURRENT PARTITION TO A NEW PARTITION
    auto new_partition = make_partition(partition, dfa_ptr->get_alphabet());
    while (!equal_partitions(partition, new_partition))
    {
        partition = new_partition;
        new_partition = make_partition(partition, dfa_ptr->get_alphabet());
    }
    // PARTITION IS THE FINAL PARTITION, CHOOSE A REPRESENTATIVE FOR EACH GROUP AND REMOVE DEAD STATES.
    std::shared_ptr<dfa> min_dfa(new dfa());
    min_dfa->set_alphabet(dfa_ptr->get_alphabet());
    for (auto group : partition)
    {
        // Choose representative and modify transitions.
        std::shared_ptr<dfa_state> grp_representative = *(group.begin());
//        if (dead_state(grp_representative))
//        {
//            continue;
//        }
        std::map<std::string, std::shared_ptr<dfa_state>> new_transitions;
        for (auto trans : grp_representative->get_transitions())
        {
            if (trans.second == nullptr) {
                continue;
            }
            std::shared_ptr<dfa_state> target_state;
            for (auto grp : partition)
            {
                bool found_target_state = false;
                for (auto s : grp)
                {
                    if (s->get_id() == trans.second->get_id())
                    {
                        target_state = *(grp.begin());
                        found_target_state = true;
                        break;
                    }
                }
                if (found_target_state)
                    break;
            }
//            if (dead_state(target_state))
//            {
//                continue;
//            }
            new_transitions[trans.first] = target_state;
        }
        grp_representative->set_transitions(new_transitions);

        // Modify ID.
        grp_representative->set_id(static_cast<state_id>(min_dfa->get_total_states()));

        for (const auto &s : group)
        {
            if (s->get_type() == START)
            {
                grp_representative->set_type(START);
                min_dfa->set_start_state(grp_representative);
            }
        }
        if (grp_representative->get_type() == ACCEPTANCE)
        {
            min_dfa->add_acceptance_state(grp_representative);
        }
        min_dfa->add_state(grp_representative);
        min_dfa->set_total_states(min_dfa->get_total_states() + 1);
    }
    return min_dfa;
}

int main(int argc, char** argv) {

    lexical_analyzer_generator gen = lexical_analyzer_generator();
    auto combined_nfa = gen.get_lexical_analyzer_file("rules.txt");
//    int i = 0;
//    for (auto s : combined_nfa->get_acceptance_states()) {
//        std::cout << s->get_token_class() << "\n";
//        std::cout << i++ << "\n";
//    }
    combined_nfa->visualize();
    auto dfa_ptr = convert_nfa_dfa(combined_nfa);
    int i = 0;
    for (auto s : dfa_ptr->get_acceptance_states()) {
        std::cout << s->get_token_class() << "\n";
        std::cout << i++ << "\n";
    }
//    dfa_ptr->visualize();
    auto min_dfa = minimize(dfa_ptr);
    min_dfa->visualize();
    draw_trans_table(min_dfa);
    return 0;
}
