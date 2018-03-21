#ifndef STATE_H
#define STATE_H

#include "../nfa_tools/lexical_rules.h"

#include <map>
#include <vector>

#define EPSILON ""
typedef unsigned int state_id;

enum state_type
{
  ACCEPTANCE,
  START,
  INTERMEDIATE
};

class state
{
protected:
    state_id id;
    state_type type;
    std::vector <regular_definition> definitions;
public:
    state (int id, state_type type, std::vector<regular_definition> definitions);
    virtual void insert_state (std::string input, std::shared_ptr<state> const& state) = 0;
    state_id get_id();
    state_type get_type();
};

#endif // STATE_H
