#include <iostream>
#include <utility>
#include "nfa.h"
#include "nfa_state.h"

#include <utility>

nfa::nfa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
        : fa(start_state, acceptance_states, total_states)
{
    nfa::start_state = start_state;
    nfa::acceptance_states = acceptance_states;
    nfa::total_states = total_states;
}

nfa::nfa() : fa()
{

}

void add_transitions_from_char_set (std::shared_ptr<char_set> st_ip,
  std::shared_ptr<nfa_state> s0, std::shared_ptr<nfa_state> sf)
{

  for (auto c : st_ip->get_characters())
  {
//            std::cout << s0->get_id() << "--" << c.first << "-->" << sf->get_id() << std::endl;
      s0->insert_transition (std::string("") + c.first, sf);
  }

  for (auto range : st_ip->get_ranges())
  {
      s0->insert_transition (range->get_range_string(), sf);
  }
    if (st_ip->is_empty())
    {
        s0->insert_transition ("", sf);
    }

}

nfa::nfa(std::shared_ptr<char_set> st_ip, int id1, int id2)
    : fa()
{
    std::shared_ptr<char_set> eps = build_epsilon_transition ();
    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (id1, START, st_ip));
    std::shared_ptr<nfa_state> sf = std::make_shared<nfa_state>(nfa_state (id2, ACCEPTANCE, eps));

    add_transitions_from_char_set (st_ip, s0, sf);


    start_state = s0;
    acceptance_states.push_back(sf);
}

nfa::nfa (std::shared_ptr<char_set> c_s)
: fa()
{
    std::shared_ptr<char_set> eps = build_epsilon_transition();
    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, c_s));
    std::shared_ptr<nfa_state> s1 =
            std::make_shared<nfa_state>(nfa_state (1, ACCEPTANCE, eps));
    add_transitions_from_char_set (c_s, s0, s1);
    start_state = s0;
    acceptance_states.push_back(s1);
}




void nfa::dfs (std::shared_ptr<state> curr_state, std::vector<bool> &visited,
               std::shared_ptr<std::ofstream> vis, bool update_acceptance_states,
                std::shared_ptr<char_set> alphabet)
{
//    std::cout << "Current state = " << curr_state->get_id() << ", input types allowed: \n";
//    for (auto x : curr_state->get_char_set()->get_characters()) {
//        std::cout << x.first << " ";
//    }
//    for (auto x : curr_state->get_char_set()->get_ranges()) {
//        std::cout << x->get_range_string() << " ";
//    }
//    std::cout << "\n";
    visited[curr_state->get_id()] = true;
    if (update_acceptance_states && curr_state->get_type() == ACCEPTANCE)
    {
        acceptance_states.push_back(curr_state);
    }
    if (alphabet != nullptr)
    {
        for (auto const& c : curr_state->get_char_set()->get_characters())
        {
            alphabet->add_character(c.first);
        }
        for (auto const& range : curr_state->get_char_set()->get_ranges())
        {
            alphabet->add_range(range->get_lower(), range->get_upper());
        }
    }

    std::map<std::string, std::vector<std::shared_ptr<nfa_state>>> transitions
            = std::static_pointer_cast<nfa_state>(curr_state)->get_transitions();

    for (auto edge : transitions)
    {
        std::string label = edge.first;
        std::vector<std::shared_ptr<nfa_state>> next_states = edge.second;
        for (auto state : next_states)
        {
            // Visualize
            if (vis != nullptr)
            {
                if (label.empty())
                {
                    label = "ϵ";
                }
                if (label == "\\")
                    label += '\\';
                // std::cout << label << std::endl;
                *vis << curr_state->get_id() << " -> " << state->get_id() << " [ label = \"" << label << "\" ];\n";
            }
            if (!visited[state->get_id()])
            {
                dfs(state, visited, vis, update_acceptance_states, alphabet);
            }
        }
    }
}


void nfa::unify(std::shared_ptr<nfa> nfa2, bool unifiy_acceptance_states)
{
    std::shared_ptr<char_set> eps = build_epsilon_transition();

    std::shared_ptr<nfa_state> s0 = std::make_shared<nfa_state>(nfa_state (0, START, eps));
    renamify(1);
    nfa2->renamify(max_id + 1);
    std::shared_ptr<nfa_state> sf = std::make_shared<nfa_state>(
      nfa_state (nfa2->max_id + 1, ACCEPTANCE, eps));

    std::shared_ptr<nfa_state> nfa2_s0 = std::static_pointer_cast<nfa_state>(nfa2->get_start_state());
    std::shared_ptr<nfa_state> nfa1_s0 = std::static_pointer_cast<nfa_state>(start_state);

    nfa1_s0->set_type(INTERMEDIATE);
    nfa2_s0->set_type(INTERMEDIATE);

    s0->insert_transition(EPSILON, nfa1_s0);
    s0->insert_transition(EPSILON, nfa2_s0);


    std::shared_ptr<nfa_state> nfa2_sf = std::static_pointer_cast<nfa_state>(nfa2->get_acceptance_states().front());
    std::shared_ptr<nfa_state> nfa1_sf = std::static_pointer_cast<nfa_state>(acceptance_states.front());

    nfa2_sf->set_type(INTERMEDIATE);
    nfa1_sf->set_type(INTERMEDIATE);


    start_state = s0;

    if (unifiy_acceptance_states)
    {
        nfa1_sf->insert_transition(EPSILON, sf);
        nfa2_sf->insert_transition(EPSILON, sf);
        acceptance_states.clear();
        acceptance_states.push_back(sf);
    }
    else
    {
        for (auto const& acc_s : nfa2->get_acceptance_states())
        {
            acceptance_states.push_back(acc_s);
        }
    }
}

void nfa::concat(std::shared_ptr<nfa> nfa2)
{
    nfa2->renamify(acceptance_states.front()->get_id() + 1);
    acceptance_states.front()->insert_transition(EPSILON, nfa2->get_start_state());

    nfa2->get_start_state()->set_type(INTERMEDIATE);
    get_acceptance_states().front()->set_type(INTERMEDIATE);

    acceptance_states.clear();
    acceptance_states.push_back(nfa2->get_acceptance_states().front());
}

void nfa::plus()
{
    std::shared_ptr<nfa> nfa2 = copy();
//    nfa2->update_acceptance_states();
    update_acceptance_states();
    nfa2->renamify(acceptance_states.front()->get_id() + 1);
    nfa2->star();
    concat(nfa2);
}

void nfa::star()
{
    start_state->insert_transition(EPSILON, acceptance_states.front());
    acceptance_states.front()->insert_transition(EPSILON, start_state);
}

std::shared_ptr<char_set> nfa::build_epsilon_transition()
{
    std::shared_ptr<char_set> empty_char_set(new char_set());
    return empty_char_set;
}


int renamifiy_start_index = 0;

void pre_copy_dfs (std::shared_ptr<state> curr_state, std::map<std::shared_ptr<state>, bool> &visited,
                    std::map <int, std::vector<std::pair<std::string, int>>> &adj,
                    std::map<int, std::shared_ptr<nfa_state>> &states)
{
  visited[curr_state] = true;
  states[(curr_state)->get_id()] = std::static_pointer_cast<nfa_state>(curr_state);

  std::map<std::string, std::vector<std::shared_ptr<nfa_state>>> transitions
          = std::static_pointer_cast<nfa_state>(curr_state)->get_transitions();
  std::vector <std::pair<std::string, int>> v;
  for (auto edge : transitions)
  {
      std::string label = edge.first;
      std::vector<std::shared_ptr<nfa_state>> next_states = edge.second;
      int i = 1;
      for (auto state : next_states)
      {
          if (!visited[state]) {
              pre_copy_dfs(state, visited, adj, states);
          }
          v.push_back ({label ,state->get_id()});
      }
  }
  adj[curr_state->get_id()] = v;
}

std::shared_ptr<nfa> nfa::copy()
{
    std::map <int, std::vector<std::pair<std::string, int>>> adj;
    std::map<int, std::shared_ptr<nfa_state>> old_states;
    std::map<std::shared_ptr<state>, bool> visited;
    pre_copy_dfs (start_state, visited, adj, old_states);
    std::map<int, std::shared_ptr<nfa_state>> new_states;

    for (auto state : old_states)
    {
      std::shared_ptr<nfa_state> old_state = state.second;
      std::shared_ptr<char_set> c_s(new char_set(*old_state->get_char_set()));
      std::shared_ptr<nfa_state> nfa_st(new nfa_state( old_state->get_id(),
                                      old_state->get_type(), c_s) );
      new_states[state.first] = nfa_st;
    }
    for (auto transition : adj)
    {
        std::vector <std::pair<std::string, int>> v = transition.second;
        int from_id = transition.first;
        for (auto edge : v)
        {
          new_states[from_id]->insert_transition (edge.first ,new_states[edge.second]);
        }
    }
    std::shared_ptr<nfa> copied_nfa(new nfa());
    copied_nfa->set_start_state(new_states[start_state->get_id()]);
    copied_nfa->update_acceptance_states();
    return  copied_nfa;
}

/**
 * @brief util function for renamify.
 * @details dfs that iterates the nfa and remame it's states ids starting from the given id.
 *
 * @param visited
 * @param id the nfa's start_state will start naming from this id and increment it to rename next states.
 */
void renamify_dfs (std::shared_ptr<state> curr_state, std::map<std::shared_ptr<state>, bool> &visited)
{
    visited[curr_state] = true;
    curr_state->set_id(renamifiy_start_index++); // update state_id

    std::map<std::string, std::vector<std::shared_ptr<nfa_state>>> transitions
            = std::static_pointer_cast<nfa_state>(curr_state)->get_transitions();

    for (auto edge : transitions)
    {
        std::string label = edge.first;
        std::vector<std::shared_ptr<nfa_state>> next_states = edge.second;
        int i = 1;
        for (auto state : next_states)
        {
            if (!visited[state]) {
                renamify_dfs(state, visited);
            }
        }
    }
}

/**
 * @brief rename nfa's states ids.
 * @details the nfa's start_state will start naming from given starting_id
 * and increment it to rename next states.
 *
 * @param starting_id
 */
void nfa::renamify (state_id starting_id)
{
    renamifiy_start_index = starting_id;
    std::map<std::shared_ptr<state>, bool> visited;
    renamify_dfs (start_state, visited);
    max_id = renamifiy_start_index - 1;
}

std::shared_ptr<char_set> nfa::get_alphabet()
{
    std::shared_ptr<char_set> alphabet(new char_set());
    std::vector<bool> visited(1000); // TODO
    dfs(start_state, visited, nullptr, true, alphabet);
    return alphabet;
}
