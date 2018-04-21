#include "dfa.h"
#include "util/util.h"
#include <climits>

dfa::dfa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
        : fa(start_state, acceptance_states, total_states) 
{
    dfa::start_state = start_state;
    dfa::acceptance_states = acceptance_states;
    dfa::total_states = total_states;
}

dfa::dfa()
{
    dfa::total_states = 0;
}


dfa::dfa(std::shared_ptr<nfa> combined_nfa) {
    // New dfa object's fields' initialization here.
    dfa::total_states = 0;
    dfa::set_alphabet(combined_nfa->get_alphabet());
    std::set<std::shared_ptr<nfa_state>> vec;
    vec.insert((std::shared_ptr<nfa_state> &&) combined_nfa->get_start_state());
    std::shared_ptr<dfa_state> init_dfa_state(new dfa_state(util::e_closure(vec), static_cast<state_id>(dfa::get_total_states())));
    dfa::set_total_states(dfa::get_total_states() + 1);
    dfa::set_start_state(init_dfa_state);
    dfa::add_state(init_dfa_state);

    std::shared_ptr<dfa_state> curr_state;
    while ((curr_state = dfa::get_unmarked_state()) != nullptr)
    {
        curr_state->set_marked(true);
        for (const auto &curr_char : dfa::get_alphabet()->get_characters())
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(util::e_closure(util::move(curr_state->get_composing_nfa_states(),
                                                                              curr_char.first)),
                                                               static_cast<state_id>(dfa::get_total_states())));
            if (new_state->get_composing_nfa_states().empty()) { // dead state
                continue;
            }
            if (new_state->equals(curr_state))
            {
                curr_state->insert_transition(dfa::get_alphabet()->get_string(curr_char.first), curr_state);
                continue;
            }
            if (!dfa::contains(new_state))
            {
                dfa::add_state(new_state);
                dfa::set_total_states(dfa::get_total_states() + 1);
                if (new_state->get_type() == ACCEPTANCE)
                {
                    dfa::add_acceptance_state(new_state);
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
                auto existing_states = dfa::get_dfa_states();
                for (auto st : existing_states)
                {
                    if (st->equals(new_state))
                    {
                        new_state = st;
                        break;
                    }
                }
            }
            curr_state->insert_transition(dfa::get_alphabet()->get_string(curr_char.first), new_state);
        }
        for (const auto &curr_range : dfa::get_alphabet()->get_ranges())
        {
            std::shared_ptr<dfa_state> new_state(new dfa_state(util::e_closure(util::move(curr_state->get_composing_nfa_states(),
                                                                              curr_range->get_range_string())),
                                                               static_cast<state_id>(dfa::get_total_states())));
            // dead state
            if (new_state->get_composing_nfa_states().empty()) { // dead state
                continue;
            }
            if (new_state->equals(curr_state))
            {
                curr_state->insert_transition(curr_range->get_range_string(), curr_state);
                continue;
            }
            if (!dfa::contains(new_state))
            {
                dfa::add_state(new_state);
                dfa::set_total_states(dfa::get_total_states() + 1);
                if (new_state->get_type() == ACCEPTANCE)
                {
                    dfa::add_acceptance_state(new_state);
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
                auto existing_states = dfa::get_dfa_states();
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
}

/// TODO: Re-check this!
void dfa::dfs(std::shared_ptr<state> curr_state, std::vector<bool> &visited,
              std::shared_ptr<std::ofstream> vis, bool update_acceptance_states,
              std::shared_ptr<char_set> alphabet) 
{
    visited[curr_state->get_id()] = true;
    if (update_acceptance_states && curr_state->get_type() == ACCEPTANCE)
    {
        acceptance_states.push_back(curr_state);
    }

    std::map<std::string, std::shared_ptr<dfa_state>> transitions
            = std::static_pointer_cast<dfa_state>(curr_state)->get_transitions();

    for (auto edge : transitions)
    {
        std::string label = edge.first;
        std::shared_ptr<dfa_state> next_state = edge.second;

        // Visualize
        if (vis != nullptr) {
            if (label.empty()) {
                label = "ϵ";
            }
            if (label == "\\")
                label += '\\';
            *vis << curr_state->get_id() << " -> " << next_state->get_id() << " [ label = \"" << label << "\" ];\n";
        }
        if (!visited[next_state->get_id()]) {
            dfs(next_state, visited, vis, update_acceptance_states, alphabet);
        }
    }
}

void dfa::add_state(std::shared_ptr<dfa_state> s) {
    dfa::dfa_states.push_back(s);
}

const std::vector<std::shared_ptr<dfa_state>> &dfa::get_dfa_states() const {
    return dfa_states;
}

std::shared_ptr<dfa_state> dfa::get_unmarked_state() {
    for (auto curr_state : dfa::dfa_states)
    {
        if (!curr_state->is_marked())
        {
            return curr_state;
        }
    }
    return nullptr;
}

/// DOUBLE CHECK THIS.
bool dfa::contains(std::shared_ptr<dfa_state> s) {
    for (auto state : dfa_states)
    {
        if (state->get_composing_nfa_states() == s->get_composing_nfa_states())
        {
            return true;
        }
    }
    return false;
}

const std::shared_ptr<char_set> &dfa::get_alphabet() const {
    return dfa::alphabet;
}

void dfa::set_alphabet(const std::shared_ptr<char_set> &alphabet) {
    // Re-implement this shit.
    dfa::alphabet = std::make_shared<char_set>(char_set());
    std::set<char> alph_chars;
    std::set<std::string> alph_ranges;
    for (auto inp : alphabet->get_characters()) {
        alph_chars.insert(inp.first);
    }
    for (auto inp : alphabet->get_ranges()) {
        alph_ranges.insert(inp->get_range_string());
    }
    for (char curr : alph_chars) {
        dfa::alphabet->add_character(curr);
    }
    for (auto curr : alph_ranges) {
        for (auto inp : alphabet->get_ranges()) {
            if (inp->get_range_string() == curr) {
                dfa::alphabet->add_range(inp->get_lower(), inp->get_upper());
                break;
            }
        }
    }
}

std::shared_ptr<dfa> dfa::minimize()
{
    std::set<std::set<std::shared_ptr<dfa_state>>> partition;
    std::set<std::shared_ptr<dfa_state>> non_acc_states, acc_states;
    for (const auto &s : dfa::get_dfa_states())
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

    auto new_partition = util::make_partition(partition, dfa::get_alphabet());
    while (!(partition == new_partition))
    {
        partition = new_partition;
        new_partition = util::make_partition(partition, dfa::get_alphabet());
    }
    std::shared_ptr<dfa> min_dfa(new dfa());
    min_dfa->set_alphabet(dfa::get_alphabet());
    for (auto group : partition)
    {
        std::shared_ptr<dfa_state> grp_representative = *(group.begin());
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

void dfa::draw_trans_table() {
    std::shared_ptr<std::ofstream> out_file(new std::ofstream());
    out_file->open("transition_table.txt");
    *out_file << "Total States: " << fa::get_total_states() << "\n";
    *out_file << "Start State(s): {" << fa::get_start_state()->get_id() << "}\n";
    *out_file << "Acceptance State(s): " << fa::get_acceptance_states().size() << "\n";
    for (auto acc_state : dfa::get_acceptance_states())
    {
        *out_file << "{" << acc_state->get_id() << "} " << acc_state->get_token_class() << "\n";
    }
    *out_file << "State ";
    std::set<char> alph_chars;
    std::set<std::string> alph_ranges;
    for (auto inp_char : dfa::get_alphabet()->get_characters())
    {
        alph_chars.insert(inp_char.first);
    }
    for (auto c : alph_chars) {
        *out_file << c << " ";
    }
    for (auto inp_range : dfa::get_alphabet()->get_ranges())
    {
        alph_ranges.insert(inp_range->get_range_string());
    }
    for (auto range : alph_ranges) {
        *out_file << range << " ";
    }
    *out_file << "\n";
    for (auto state : dfa::get_dfa_states())
    {
        *out_file << "{" << state->get_id() << "} ";
        for (auto inp_char : dfa::get_alphabet()->get_characters())
        {
            auto target_state = state->get_next_state(inp_char.first);
            if (target_state == nullptr)
            {
                *out_file << "{-} ";
            }
            else
            {
                *out_file << "{" << target_state->get_id() << "} ";
            }
        }
        for (auto inp_range : dfa::get_alphabet()->get_ranges())
        {
            auto target_state = state->get_next_state(inp_range->get_range_string());
            if (target_state == nullptr)
            {
                *out_file << "{-} ";
            }
            else
            {
                *out_file << "{" << target_state->get_id() << "} ";
            }
        }
        *out_file << "\n";
    }
}
