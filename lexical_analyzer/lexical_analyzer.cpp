#include "lexical_analyzer.h"

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
 *  Splits a set of elements represented by a string on comma as a delimiter, removes
 *  brackets and returns tokens in a vector, example for the input string: {1,2,3}.
 */
void split_set_on_comma (std::vector<std::string> &, std::string &);

/**
 *  Converts string to integer using std::stringstream.
 */
int string_to_integer (std::string &);

/**
 *  Generates a vector of a given size of DFA states.
 */
std::vector<std::shared_ptr<dfa_state> > generate_dfa_states (int);

/**
 *  Checks whether the DFA state represented by the given ID is a start
 *  state or not.
 */
bool is_start_dfa_state (int);

/**
 *  Checks whether the DFA state represented by the given ID is an
 *  acceptance state or not.
 */
bool is_acceptance_dfa_state (int);

/**
 *  Gets the state type of the DFA state represented by the gived ID.
 */
state_type get_state_type (int);

lexical_analyzer::lexical_analyzer (std::string lexical_analyzer_file
                                        , std::string code_file) {
    this->lexical_analyzer_file = lexical_analyzer_file;
    this->code_file = code_file;
}

token lexical_analyzer::get_next_token () {
    
}

std::shared_ptr<dfa> lexical_analyzer::parse_lexical_analyzer_machine () {
    // Opens an input file stream on the lexical analyzer machine file.
    ifstream lex_in_file;
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
                dfa_states = generate_dfa_states (total_states);
                break;
            case TRANSITION_TABLE_INPUT_LINE:
                vec.erase (vec.begin ());
                transition_table_input = vec;
                break;
            default:
                // Build the DFA online.
        }
        line_counter++;
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


std::vector<std::shared_ptr<dfa_state> > generate_dfa_states (int count) {
    std::vector<std::shared_ptr<dfa_state> > dfa_states_vec;
    for (unsigned int i = 0 ; i < count ; i++) {
        char_set dfa_state_char_set;
        std::shared_ptr<dfa_state> s = std::make_shared<dfa_state> (dfa_state (
                                            i, get_state_type (i), dfa_state_char_set));
        dfa_states_vec.push_back (s);

    }
    return dfa_states_vec;
}

bool is_start_dfa_state (int state_id) {
    return state_id == start_state_id;
}

bool is_acceptance_dfa_state (int state_id) {
    for (unsigned int i = 0 ; i < acceptance_states_ids.size () ; i++) {
        if (acceptance_states_ids[i] == state_id)
            return true;
    }
    return false;
} 

state_type get_state_type (int state_id) {
    if (is_start_dfa_state (state_id)) {
        return state_type::START;
    } else if (is_acceptance_dfa_state (start_id)) {
        return state_type::ACCEPTANCE;
    } else {
        return state_type::INTERMEDIATE;
    }
}