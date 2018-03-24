#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "../lexical_analyzer_generator/finite_automata/dfa_state.h"
#include "../lexical_analyzer_generator/finite_automata/dfa.h"
#include <string>
#include <vector>

struct acceptance_state {
  int state_id;
  std::string token_class;
};

struct token {
  std::string lexeme;
  std::string token_class;
  int str_pos;
};

class lexical_analyzer {
private:
  int start_state_id;
  int total_states;
  int matcher_pos;
  int prev_matcher_pos;
  std::string input_str;
  std::shared_ptr<dfa> dfa_ptr;
  std::vector<acceptance_state> acceptance_states_info;
  std::vector<std::string> transition_table_inputs;
  std::shared_ptr<dfa> parse_lexical_analyzer_machine (std::string);
public:
  lexical_analyzer (std::string &, std::string &);
  lexical_analyzer (std::shared_ptr<dfa> &, std::string &);
  int get_next_token (token &);
  const std::shared_ptr<dfa> &get_dfa() const;
};

#endif // LEXICAL_ANALYZER_H
