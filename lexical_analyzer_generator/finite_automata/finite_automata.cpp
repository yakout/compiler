#include <iostream>
#include <fstream>
#include <cstdlib>
#include <array>
#include <utility>
#include <set>
#include "finite_automata.h"
#include "nfa_state.h"

fa::fa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states)
{
    fa::start_state = std::move(start_state);
    fa::acceptance_states = std::move(acceptance_states);
    fa::total_states = total_states;
}

fa::fa(const fa& fa_to_copy)
    : start_state(fa_to_copy.get_start_state()->copy()),
  acceptance_states(),
  total_states(fa_to_copy.get_total_states())
{

}

fa::fa()
{
    fa::total_states = 0;
}

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer{};
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void fa::visualize()
{
    std::shared_ptr<std::ofstream> visualizer(new std::ofstream());
    visualizer->open("fsm.dot");
    *visualizer <<
                "digraph finite_state_machine {\n"
                        "\trankdir=LR;\n"
                        "\tsize=\"500,300\"\n"
                        "\tnode [shape = doublecircle]; ";
    for (const auto &s : acceptance_states)
    {
        *visualizer << s->get_id() << " ";
    }
    *visualizer << ";\n"
            "\tnode [shape = none] \"\";\n"
            "\tnode [shape = circle];\n"
            "\"\" -> " << start_state->get_id() << "\n";


    int MAX_DFS = 1000;
    std::vector<bool> visited(MAX_DFS);
    dfs(start_state, visited, visualizer, false, nullptr);
    *visualizer << "}\n";
    visualizer->close();

    #ifdef __linux__
        exec("dot -Tpng -O fsm.dot");
    #elif _WIN32
        system ("\"C:\\\\Program Files (x86)\\\\Graphviz2.38\\\\bin\\\\dot\" -Tpng  -O fsm.dot");
    #elif __APPLE__
        exec("dot -Tpng -O fsm.dot");
        exec("open fsm.dot.png");
    #endif
}

const std::shared_ptr<state> &fa::get_start_state() const
{
    return start_state;
}

const std::vector<std::shared_ptr<state>> &fa::get_acceptance_states() const
{
    return acceptance_states;
}

int fa::get_total_states() const
{
    return total_states;
}


void fa::set_start_state(std::shared_ptr<state> new_state)
{
    start_state = new_state;
}

void fa::set_acceptance_states(std::vector<std::shared_ptr<state>> new_acceptance_states)
{
    acceptance_states = new_acceptance_states;
}

void fa::set_total_states(int total_states)
{
    fa::total_states = total_states;
}

void fa::add_acceptance_state(std::shared_ptr<state> s)
{
    fa::acceptance_states.push_back(s);
}

void fa::update_acceptance_states()
{
    std::vector<bool> visted(static_cast<unsigned long>(1000)); // TODO
    dfs(start_state, visted, nullptr, true, nullptr);
}

int fa::get_max_id() {
    return max_id;
}

void fa::set_acceptance_states_priority(int pri)
{
  for (auto state : acceptance_states)
  {
    state->set_priority(pri);
  }
}

void fa::set_acceptance_states_token_class(std::string token_class)
{
  for (auto state : acceptance_states)
  {
    state->set_token_class(token_class);
  }
}
