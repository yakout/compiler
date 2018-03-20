#ifndef STATE_H
#define STATE_H

#include "../nfa_tools/lexical_rules.h"

#include <map>
#include <vector>

typedef unsigned int state_id;

enum state_type
{
  ACCEPTANCE,
  START,
  INTERMEDIATE
};

class State
{
private:
  state_id s_id;
  state_type type;
  std::vector <regular_definition> definitions;
public:
  State (int id, state_type type, std::vector<regular_definition> definitions);
  virtual State* get_next_state (char input) = 0;
  void insert_state (std::string input, State* state, ...);
};

class NFA_State : public State
{
public:
  NFA_State (int id, state_type type, std::vector<regular_definition> definitions);
  State* get_next_state (char input) override;
private:
 	std::map <std::string, std::vector<NFA_State>> transitions;
};

class DFA_State : public State
{
public:
  DFA_State (int id, state_type type, std::vector<regular_definition> definitions);
  State* get_next_state (char input) override;

private:
 	std::map <std::string, DFA_State> transitions;
};

#endif // STATE_H
