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

class State
{
protected:
    state_id id;
    state_type type;
    std::vector <regular_definition> definitions;
public:
    State (int id, state_type type, std::vector<regular_definition> definitions);
    virtual void insert_state (std::string input, std::shared_ptr<State> const& state) = 0;
    state_id get_id();
    state_type get_type();
};

class NFA_State : public State
{
private:
    std::map <std::string, std::vector<std::shared_ptr<NFA_State>>> transitions;
public:
    NFA_State (int id, state_type type, std::vector<regular_definition> definitions);
    void insert_state (std::string input, std::shared_ptr<State> const& state) override;
    std::vector<std::shared_ptr<NFA_State>> get_next_state (char input);
    std::map <std::string, std::vector<std::shared_ptr<NFA_State>>> get_transitions();
};

class DFA_State : public State
{
private:
    std::map <std::string, std::shared_ptr<DFA_State>> transitions;
public:
    DFA_State (int id, state_type type, std::vector<regular_definition> definitions);
    void insert_state (std::string input, std::shared_ptr<State> const& state) override;
    std::shared_ptr<DFA_State> get_next_state (char input);
    std::map <std::string, std::shared_ptr<DFA_State>> get_transitions();
};

#endif // STATE_H
