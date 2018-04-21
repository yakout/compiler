#ifndef STATE_H
#define STATE_H

#include "../nfa_tools/lexical_rules.h"

#include <map>
#include <vector>
#include <memory>

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
    std::shared_ptr<char_set> state_input;
    std::string token_class;
    int priority;

public:
    state (state_id id, state_type type, std::shared_ptr<char_set> st_ip);
    state (const state&);
    state ();

    virtual void insert_transition (std::string input, std::shared_ptr<state> const& state) = 0;
    /**
     * makes a copy of the state which used in copying nfa.
     * @return shared_ptr to a copy state.
     */
    virtual std::shared_ptr<state> copy() = 0;

    // getters
    const state_id& get_id() const;
    const state_type& get_type() const;
    const std::shared_ptr<char_set> get_char_set() const;
    const std::string get_token_class () const;
    const int get_token_class_priority () const;
    // setters
    void set_type (state_type);
    void set_id (state_id);
    void set_char_set (std::shared_ptr<char_set>);
    void set_token_class (std::string);
    void set_priority (int);
};

#endif // STATE_H
