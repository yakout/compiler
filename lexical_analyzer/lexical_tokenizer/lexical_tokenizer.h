#ifndef LEXICAL_TOKENIZER_H
#define LEXICAL_TOKENIZER_H

#include "../lexical_analyzer_generator/finite_automata/dfa_state.h"
#include "../lexical_analyzer_generator/finite_automata/dfa.h"
#include "token.h"
#include <string>
#include <vector>

struct acceptance_state {
  int state_id;
  std::string token_class;
};

class lexical_tokenizer {
private:
  int start_state_id;
  int total_states;
  int matcher_pos;
  int prev_matcher_pos;
  std::string input_str;
  std::shared_ptr<dfa> dfa_ptr;
  std::vector<acceptance_state> acceptance_states_info;
  std::vector<std::string> transition_table_inputs;
  std::shared_ptr<dfa> parse_lexical_analyzer_machine (char *transition_table_file);
public:
  lexical_tokenizer (char *transition_table_file, char *code_file);
  lexical_tokenizer (std::shared_ptr<dfa> &, char *code_file);
  int get_next_token (token &);
  const std::shared_ptr<dfa> get_dfa() const;
};

#endif // LEXICAL_ANALYZER_H
