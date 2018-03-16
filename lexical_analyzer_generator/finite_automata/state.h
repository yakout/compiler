#ifndef STATE_H
#define STATE_H

#include <map>
#include <vector>

typedef state_id unsigned int;

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
public:
  State(int id, state_type type);
  virtual State get_next_state (char input) = 0;
};

class NFA_State : public State
{
private:
 	map <char, vector<State>> transitions;
};

class DFA_State : public State
{
private:
 	map <char, State> transitions;
};

#endif // STATE_H
