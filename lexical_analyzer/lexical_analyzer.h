#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "../lexical_analyzer_generator/finite_automata/dfa_state.h"
#include "../lexical_analyzer_generator/finite_automata/dfa.h"
#include "token.h"
#include <string>
#include <vector>

class lexical_analyzer
{
private:
  std::string lexical_analyzer_file;
  std::string code_file;
  int start_state_id;
  std::vector<int> acceptance_states_ids;
  int total_states;
  int total_inputs;
  std::shared_ptr<dfa> dfa_ptr;
  std::vector<std::string> transition_table_inputs;
  std::shared_ptr<dfa> parse_lexical_analyzer_machine ();
public:
  lexical_analyzer (std::string &, std::string &);
  token get_next_token ();
};

#endif // LEXICAL_ANALYZER_H
