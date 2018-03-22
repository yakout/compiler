#include "lexical_analyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

/**
 *  Definitions of some constants representing the lines ordering within
 *  the lexical analyzer's transition table file.
 */
#define START_STATE_LINE 0
#define ACCEPTANCE_STATES_LINE 1
#define TOTAL_INPUTS_LINE 2
#define TOTAL_STATES_LINE 3
#define TRANSITION_TABLE_INPUT_LINE 4

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
std::vector<std::shared_ptr<dfa_state>> generate_dfa_states (int, int
                , std::vector<std::string> &
                , std::vector<int> &);

/**
 *  Checks whether the DFA state represented by the given ID is a start
 *  state or not.
 */
bool is_start_dfa_state (int, int);

/**
 *  Checks whether the DFA state represented by the given ID is an
 *  acceptance state or not.
 */
bool is_acceptance_dfa_state (int, std::vector<int> &);

/**
 *  Gets the state type of the DFA state represented by the gived ID.
 */
state_type get_state_type (int, int, std::vector<int> &);

/**
 *  Builds a character set using all transition table possible inputs.
 */
void build_char_set (char_set &, std::vector<std::string> &);

/**
 *  Adjusts DFA state outgoing transitions according to a row parsed
 *  from the transition table, example: "0   1   2   3" which means that 
 *  that state(0) will go to state(1) upon getting any input that matches 
 *  input specified by the first column of the transition table.
 */
void adjust_dfa_state_transitions (std::vector<std::shared_ptr<dfa_state>> &
                                            , std::vector<std::string> &
                                            , std::vector<std::string> &);


lexical_analyzer::lexical_analyzer (std::string &lexical_analyzer_file
                                                , std::string &code_file) {
    this->lexical_analyzer_file = lexical_analyzer_file;
    this->code_file = code_file;
}

token lexical_analyzer::get_next_token () {
    
}

std::shared_ptr<dfa> lexical_analyzer::parse_lexical_analyzer_machine () {
    // Opens an input file stream on the lexical analyzer machine file.
    std::ifstream lex_in_file;
    lex_in_file.open (lexical_analyzer_file.c_str ());
    std::string line;
    std::vector<std::string> vec;
    std::vector<std::shared_ptr<dfa_state>> dfa_states;
    int line_counter = 0;
    while (getline (lex_in_file, line)) {
        split_str_on_space (vec, line);
        switch (line_counter) {
            case START_STATE_LINE:
                start_state_id = string_to_integer (vec[2]);
                break;
            case ACCEPTANCE_STATES_LINE:
                for (unsigned int i = 2 ; i < vec.size () ; i++) {
                    acceptance_states_ids.push_back (string_to_integer (vec[i]));
                }
                break;
            case TOTAL_INPUTS_LINE:
                total_inputs = string_to_integer (vec[2]);
                break;
            case TOTAL_STATES_LINE:
                total_states = string_to_integer (vec[2]);
                dfa_states = generate_dfa_states (total_states
                                                    , start_state_id
                                                    , transition_table_inputs
                                                    , acceptance_states_ids);
                break;
            case TRANSITION_TABLE_INPUT_LINE:
                vec.erase (vec.begin ());
                transition_table_inputs = vec;
                break;
            default:
                adjust_dfa_state_transitions (dfa_states, vec
                                                    , transition_table_inputs);
        }
        line_counter++;
        vec.clear ();
    }
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
    // Check whether it is a set or not.
    if (str.length () > 2) {
        // Remove brackets.
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
                            , std::vector<int> &acceptance_states_ids) {
    std::vector<std::shared_ptr<dfa_state>> dfa_states_vec;
    for (unsigned int i = 0 ; i < count ; i++) {
        char_set dfa_state_char_set;
        build_char_set (dfa_state_char_set, transition_table_inputs);
        std::shared_ptr<dfa_state> s = std::make_shared<dfa_state> (
                        dfa_state (i, get_state_type (i, start_state_id
                                            , acceptance_states_ids), dfa_state_char_set));
        dfa_states_vec.push_back (s);
    }
    return dfa_states_vec;
}

bool is_start_dfa_state (int state_id, int start_state_id) {
    return state_id == start_state_id;
}

bool is_acceptance_dfa_state (int state_id
                                , std::vector<int> &acceptance_states_ids) {
    for (unsigned int i = 0 ; i < acceptance_states_ids.size () ; i++) {
        if (acceptance_states_ids[i] == state_id)
            return true;
    }
    return false;
} 

state_type get_state_type (int state_id, int start_state_id
                                , std::vector<int> &acceptance_states_ids) {
    if (is_start_dfa_state (state_id, start_state_id)) {
        return state_type::START;
    } else if (is_acceptance_dfa_state (state_id, acceptance_states_ids)) {
        return state_type::ACCEPTANCE;
    } else {
        return state_type::INTERMEDIATE;
    }
}

void build_char_set (char_set &ch_set
                        , std::vector<std::string> &transition_table_inputs) {
    for (unsigned int i = 0 ; i < transition_table_inputs.size () ; i++) {
        if (transition_table_inputs[i].length () == 3) {
            ch_set.add_range (transition_table_inputs[i][0]
                                        , transition_table_inputs[i][2]);
        } else {
            ch_set.add_character (transition_table_inputs[i][0]);
        }
    }
    return;
}

void adjust_dfa_state_transitions (std::vector<std::shared_ptr<dfa_state>> 
                        &dfa_states_vec, std::vector<std::string> &vec
                        , std::vector<std::string> &transition_table_inputs) {
    int curr_dfa_state = string_to_integer (vec[0]);
    for (unsigned int i = 1 ; i < vec.size () ; i++) {
        if (vec[i].compare("-")) {
            dfa_states_vec[curr_dfa_state]->insert_transition (
                        transition_table_inputs[i - 1]
                        , dfa_states_vec[string_to_integer (vec[i])]);
        }
    }
}