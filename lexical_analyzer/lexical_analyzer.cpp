#include "lexical_analyzer.h"

void split_str_on_space (std::vector<std::string> &, std::string &);
void split_set_on_comma (std::vector<std::string> &, std::string &);
int string_to_integer (std::string &);
std::vector<std::shared_ptr<dfa_state>> generate_dfa_states (int);

lexical_analyzer::lexical_analyzer (std::string lexical_analyzer_file
                                        , std::string code_file) {
    this->lexical_analyzer_file = lexical_analyzer_file;
    this->code_file = code_file;
}

token lexical_analyzer::get_next_token () {
    
}

std::shared_ptr<dfa> lexical_analyzer::parse_lexical_analyzer_machine () {
    // Open an input file stream on the lexical analyzer machine file.
    ifstream lex_in_file;
    lex_in_file.open (lexical_analyzer_file.c_str ());
    std::string line;
    std::vector<std::string> vec;
    std::vector<std::shared_ptr<dfa_state>> dfa_states;
    int line_counter = 0;
    while (getline (lex_in_file, line)) {
        split_str_on_space (vec, line);
        if (line_counter == 0) {
            initial_state_id = string_to_integer (vec[2]);
        } else if (line_counter == 1) {
            for (int i = 2 ; i < vec.size () ; i++) {
                acceptance_states_ids.push_back (string_to_integer (vec[i]));
            }
        } else if (line_counter == 2) {
            total_inputs = string_to_integer (vec[2]);
        } else if (line_counter == 3) {
            total_states = string_to_integer (vec[2]);
            dfa_states = generate_dfa_states (total_states);
        } else if (line_counter == 4) {
            vec.erase (vec.begin ());
            transition_table_input = vec;
        }
        // Build the DFA online.
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


std::vector<std::shared_ptr<dfa_state>> generate_dfa_states (int count) {

}