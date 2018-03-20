#ifndef STATE_H
#define STATE_H

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
public:
  State (int id, state_type type);
  //virtual State* get_next_state (char input) = 0;
};

class NFA_State : public State
{
public:
  NFA_State (int id, state_type type);
  //State* get_next_state (char input);
private:
 	std::map <char, std::vector<NFA_State>> transitions;
};

class DFA_State : public State
{
public:
  DFA_State(int id, state_type type);
  //State* get_next_state (char input);
private:
 	std::map <char, DFA_State> transitions;
};

#endif // STATE_H
