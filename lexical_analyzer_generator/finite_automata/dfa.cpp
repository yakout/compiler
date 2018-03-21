//
// Created by awalid on 3/21/18.
//

#include "dfa.h"

#include <utility>

dfa::dfa (std::shared_ptr<state> start_state, std::shared_ptr<state> acceptance_state)
        : fa(std::move(start_state), std::move(acceptance_state))
{

}



void dfa::dfs(std::shared_ptr<state> curr_state, std::vector<bool> &visited, std::shared_ptr<std::ofstream> vis) {

}