#include <climits>
#include "dfa_state.h"

dfa_state::dfa_state (int id, state_type type, std::shared_ptr<char_set> st_ip)
        : state (id, type, st_ip)
{
    dfa_state::marked = false;
    dfa_state::state_input = std::make_shared<char_set>(char_set());
    dfa_state::priority = INT_MAX;
}

dfa_state::dfa_state(std::set<std::shared_ptr<nfa_state>> nfa_states, state_id id) {
    // nfa states composing dfa state.
    dfa_state::composing_nfa_states = nfa_states;

    // Setting dfa_state state_input
    dfa_state::state_input = std::make_shared<char_set>(char_set());
    for (const auto &state : dfa_state::composing_nfa_states)
    {
        auto nfa_state_characters = state->get_char_set()->get_characters();
        auto nfa_state_ranges = state->get_char_set()->get_ranges();
        for (auto c : nfa_state_characters)
        {
            dfa_state::state_input->add_character(c.first);
        }
        for (const auto &range : nfa_state_ranges)
        {
            dfa_state::state_input->add_range(range->get_lower(),range->get_upper());
        }
    }

    // Setting id.
    dfa_state::id = id;

    // Initializing token_class
    dfa_state::token_class = std::string();

    // Determining type. ASSUMPTION: state can't be in more than one type simultaneously.
    dfa_state::type = INTERMEDIATE;
    for (const auto &curr : nfa_states)
    {
        if (curr->get_type() == START)
        {
            dfa_state::type = START;
            break;
        }
        else if (curr->get_type() == ACCEPTANCE)
        {
            dfa_state::type = ACCEPTANCE;
            break;
        }
    }
    dfa_state::marked = false;
    dfa_state::priority = INT_MAX;
}

void dfa_state::insert_transition (std::string input, std::shared_ptr<state> const& state)
{
    transitions[input] = std::static_pointer_cast<dfa_state>(state);
}

std::shared_ptr<dfa_state> dfa_state::get_next_state(char input)
{
    std::string key = state_input->get_string(input);
    if (key.empty() && input != '\0')
        return nullptr;
    return transitions[key];
}

std::map<std::string, std::shared_ptr<dfa_state>> dfa_state::get_transitions()
{
    return transitions;
}

const std::set<std::shared_ptr<nfa_state>> &dfa_state::get_composing_nfa_states() const {
    return composing_nfa_states;
}

bool dfa_state::is_marked() const {
    return marked;
}

void dfa_state::set_marked(bool marked) {
    dfa_state::marked = marked;
}

bool dfa_state::equals(std::shared_ptr<dfa_state> s) {
    return dfa_state::composing_nfa_states == s->get_composing_nfa_states();
}

std::shared_ptr<state> dfa_state::copy() {
    return std::make_shared<dfa_state>(*this);
}

std::shared_ptr<dfa_state> dfa_state::get_next_state(std::string input) {
    return transitions[input];
}

void dfa_state::set_transitions(const std::map<std::string, std::shared_ptr<dfa_state>> &transitions) {
    dfa_state::transitions = transitions;
}
