#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "../lexical_nalyzer_generator/finite_automata/dfa_state.h"
#include "token.h"
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
  std::shared_ptr<dfa> dfa;
  std::vector<std::string> transition_table_input;
  std::shared_ptr<dfa> parse_lexical_analyzer_machine ();
public:
  lexical_analyzer (ifsteam &, ifstream &);
  token get_next_token ();
};

#endif // LEXICAL_ANALYZER_H
