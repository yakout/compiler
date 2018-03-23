#include "lexical_analyzer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>

/**
 *  Definitions of some constants representing the lines ordering within
 *  the lexical analyzer's transition table file.
 */
#define TOTAL_STATES_LINE 0
#define START_STATE_LINE 1
#define ACCEPTANCE_STATES_LINE 2
#define TRANSITION_TABLE_INPUT_LINE 3

/**
 *  Splits a string on whitespace as a delimiter and returns tokens in a vector.
 */
void split_str_on_space (std::vector<std::string> &, std::string &);

/**
 *  Splits a set of elements represented by a string on comma as a delimiter
 *  , removes brackets and returns tokens in a vector, example for the
 *  input string: {1,2,3}.
 */
void split_set_on_comma (std::vector<std::string> &, std::string &);

/**
 *  Converts string to integer using std::stringstream.
 */
int string_to_integer (std::string &);

/**
 *  Generates a vector of a given size of DFA states adjusting their
 *  character sets according to all possible inputs of transition table.
 */
std::vector<std::shared_ptr<dfa_state>> generate_dfa_states (int
                        , int start_state_id
                        , std::vector<std::string> &
                        , std::vector<acceptance_state> &);

/**
 *  Checks whether the DFA state represented by the given ID is an
 *  acceptance state or not if yes it returns the index of this acceptance
 *  state info in the acceptance states info vector else it returns -1.
 */
int is_acceptance_dfa_state (int, std::vector<acceptance_state> &);

/**
 *  Modifies a character set by adding the given the string to its content,
 *  whether it respresents a character range or just a single character.
 */
void modify_char_set (std::shared_ptr<char_set> &ch_set, std::string &str);

/**
 *  Adjusts DFA state outgoing transitions according to a row parsed
 *  from the transition table, example: "0   1   2   3" which means that
 *  that state(0) will go to state(1) upon getting any input that matches
 *  input specified by the first column of the transition table.
 */
void adjust_dfa_state_transitions (std::vector<std::shared_ptr<dfa_state>> &
                                            , std::vector<std::string> &
                                            , std::vector<std::string> &);

/**
 *  Returns a vector of acceptance states containing the state objects
 *  corresponding to the given acceptance states IDs.
 */
std::vector<std::shared_ptr<state>> get_acceptance_states_from_ids (
                                    std::vector<std::shared_ptr<dfa_state>> &
                                    ,std::vector<acceptance_state> &);

/**
 *  Adds state objects to DFA object.
 */
void add_states_to_dfa (std::shared_ptr<dfa> &
                                , std::vector<std::shared_ptr<dfa_state>> &);


lexical_analyzer::lexical_analyzer (std::string &lexical_analyzer_file
                                                , std::string &code_file) {
    lexical_analyzer::lexical_analyzer_file = lexical_analyzer_file;
    lexical_analyzer::code_file = code_file;
    dfa_ptr = lexical_analyzer::parse_lexical_analyzer_machine ();
}

lexical_analyzer::lexical_analyzer (std::shared_ptr<dfa> &dfa_ptr
                            , std::string &code_file) {
    lexical_analyzer::dfa_ptr = dfa_ptr;
    lexical_analyzer::code_file = code_file;
}

token lexical_analyzer::get_next_token () {

}

const std::shared_ptr<dfa> &lexical_analyzer::get_dfa() const {
    return dfa_ptr;
}

std::shared_ptr<dfa> lexical_analyzer::parse_lexical_analyzer_machine () {
    std::ifstream lex_in_file;
    lex_in_file.open (lexical_analyzer_file.c_str ());
    std::string line;
    std::vector<std::string> vec;
    std::vector<std::shared_ptr<dfa_state>> dfa_states;
    int line_counter = 0;
    while (std::getline (lex_in_file, line)) {
        split_str_on_space (vec, line);
        if (line_counter == TOTAL_STATES_LINE) {
            total_states = string_to_integer (vec[2]);
        } else if (line_counter == START_STATE_LINE) {
            start_state_id = string_to_integer (vec[2]);
        } else if (line_counter == ACCEPTANCE_STATES_LINE) {
            int acceptance_states_count = string_to_integer (vec[2]);
            vec.clear ();
            while (acceptance_states_count--
                            && std::getline (lex_in_file, line)) {
                split_str_on_space (vec, line);
                acceptance_state accept_state;
                accept_state.state_id = string_to_integer (vec[0]);
                accept_state.token_class = vec[1];
                acceptance_states_info.push_back (accept_state);
                vec.clear ();
            }
        } else if (line_counter == TRANSITION_TABLE_INPUT_LINE) {
            vec.erase (vec.begin ());
            transition_table_inputs = vec;
            dfa_states = generate_dfa_states (total_states
                                , start_state_id, transition_table_inputs
                                , acceptance_states_info);
        } else {
            adjust_dfa_state_transitions (dfa_states, vec
                                                    , transition_table_inputs);
        }
        line_counter++;
        vec.clear ();
    }

    std::vector<std::shared_ptr<state>> acceptance_states = get_acceptance_states_from_ids (
                    dfa_states, acceptance_states_info);
    std::shared_ptr<dfa> new_dfa (new dfa (dfa_states[start_state_id],
                                                    acceptance_states, total_states));
    add_states_to_dfa (new_dfa, dfa_states);
    return new_dfa;
}

void split_str_on_space (std::vector<std::string> &vec, std::string &str) {
    std::stringstream ss_str (str);
    std::string token;
    while (getline (ss_str, token, ' ')) {
        split_set_on_comma (vec, token);
    }
    return;
}

void split_set_on_comma (std::vector<std::string> &vec, std::string &str) {
    if (str.length () > 2) {
        str.erase (remove (str.begin (), str.end (), '{'), str.end ());
        str.erase (remove (str.begin (), str.end (), '}'), str.end ());
    }

    std::stringstream ss_str (str);
    std::string token;

    while (getline (ss_str, token, ',')) {
        vec.push_back (token);
    }
    return;
}

int string_to_integer (std::string &str) {
    std::stringstream ss_str (str);
    int int_num;
    ss_str >> int_num;
    return int_num;
}

std::vector<std::shared_ptr<dfa_state>> generate_dfa_states (int count
                            , int start_state_id
                            , std::vector<std::string> &transition_table_inputs
                            , std::vector<acceptance_state> &acceptance_states_info) {
    std::vector<std::shared_ptr<dfa_state>> dfa_states_vec;
    for (unsigned int i = 0 ; i < count ; i++) {
        std::shared_ptr<char_set> dfa_state_char_set = std::make_shared<char_set>(char_set ());
        std::shared_ptr<dfa_state> s;
        int acceptance_state_index = is_acceptance_dfa_state (i, acceptance_states_info);
        if (acceptance_state_index != -1) {
            s = std::make_shared<dfa_state>(dfa_state (i, state_type::ACCEPTANCE
                , dfa_state_char_set, acceptance_states_info[acceptance_state_index].token_class));
        } else if (i == start_state_id) {
            s = std::make_shared<dfa_state>(dfa_state (i, state_type::START
                                                , dfa_state_char_set));
        } else {
            s = std::make_shared<dfa_state>(dfa_state (i, state_type::INTERMEDIATE
                                                , dfa_state_char_set));
        }
        dfa_states_vec.push_back (s);
    }
    return dfa_states_vec;
}

int is_acceptance_dfa_state (int state_id
                    , std::vector<acceptance_state> &acceptance_states_info) {
    for (int i = 0 ; i < acceptance_states_info.size () ; i++) {
        if (acceptance_states_info[i].state_id == state_id)
            return i;
    }
    return -1;
}

void modify_char_set (std::shared_ptr<char_set> &ch_set
                        , std::string &str) {
    if (str.length () == 3) {
        ch_set->add_range (str[0], str[2]);
    } else {
        ch_set->add_character (str[0]);
    }
    return;
}

void adjust_dfa_state_transitions (std::vector<std::shared_ptr<dfa_state>>
                        &dfa_states_vec, std::vector<std::string> &vec
                        , std::vector<std::string> &transition_table_inputs) {
    int curr_dfa_state = string_to_integer (vec[0]);
    std::shared_ptr<char_set> ch_set = std::make_shared<char_set>(
                char_set (*(dfa_states_vec[curr_dfa_state]->get_char_set ())));
    for (unsigned int i = 1 ; i < vec.size () ; i++) {
        if (vec[i].compare("-")) {
            modify_char_set (ch_set, transition_table_inputs[i - 1]);
            dfa_states_vec[curr_dfa_state]->insert_transition (
                        transition_table_inputs[i - 1]
                        , dfa_states_vec[string_to_integer (vec[i])]);
        }
    }
    dfa_states_vec[curr_dfa_state]->set_char_set (ch_set);
    return;
}

std::vector<std::shared_ptr<state>> get_acceptance_states_from_ids (
                        std::vector<std::shared_ptr<dfa_state>> &dfa_states_vec
                                    ,std::vector<acceptance_state> &acceptance_states_info) {
    std::vector<std::shared_ptr<state>> acceptance_dfa_states;
    for (auto s : acceptance_states_info) {
        acceptance_dfa_states.push_back (dfa_states_vec[s.state_id]);
    }
    return acceptance_dfa_states;
}


void add_states_to_dfa (std::shared_ptr<dfa> &dfa_ptr
                        , std::vector<std::shared_ptr<dfa_state>> &dfa_states) {
    for (auto s : dfa_states) {
        dfa_ptr->add_state (s);
    }
}
