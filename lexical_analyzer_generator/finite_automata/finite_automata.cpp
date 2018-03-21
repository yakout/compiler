#include <iostream>
#include <fstream>
#include <array>
#include "finite_automata.h"

FA::FA (std::shared_ptr<State> start, std::shared_ptr<State> acpt)
        : start_state(start), acceptance_state(acpt)
{

}


NFA::NFA (std::shared_ptr<State> start_state, std::shared_ptr<State> acceptance_state)
        : FA(start_state, acceptance_state)
{

}

DFA::DFA (std::shared_ptr<State> start_state, std::shared_ptr<State> acceptance_state)
        : FA(start_state, acceptance_state)
{

}


Transition_Table FA::get_transition_table ()
{
    return Transition_Table();
}


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}


void FA::visualize() {
    std::vector<bool> visited(6);

    std::shared_ptr<std::ofstream> visualizer(new std::ofstream());
    visualizer->open("fsm.dot");
    *visualizer <<
                "digraph finite_state_machine {\n"
                        "\trankdir=LR;\n"
                        "\tsize=\"8,5\"\n"
                        "\tnode [shape = doublecircle]; "
                << acceptance_state->get_id() << ";\n"
                        "\tnode [shape = none] \"\";\n"
                        "\tnode [shape = circle];\n"
                        "\"\" -> " << start_state->get_id() << "\n";

    dfs(start_state, visited, visualizer);

    *visualizer << "}\n";
    visualizer->close();
    exec("dot -Tpng -O fsm.dot");
    exec("open fsm.dot.png");
}

void NFA::dfs (std::shared_ptr<State> curr_state, std::vector<bool> visited, std::shared_ptr<std::ofstream> vis)
{
    visited[curr_state->get_id()] = true;

    std::map<std::string, std::vector<std::shared_ptr<NFA_State>>> transitions
            = std::static_pointer_cast<NFA_State>(curr_state)->get_transitions();

    for (auto edge : transitions)
    {
        std::string label = edge.first;
        std::vector<std::shared_ptr<NFA_State>> next_states = edge.second;
        for (auto state : next_states)
        {
            if (!visited[state->get_id()]) {
                // Plot
                if (vis != nullptr) {
                    if (label.empty()) {
                        label = "E";
                    }
                    *vis << curr_state->get_id() << " -> " << state->get_id() << " [ label = \"" << label << "\" ];\n";
                }
                dfs(state, visited, vis);
            }
        }
    }
}

void DFA::dfs(std::shared_ptr<State> curr_state, std::vector<bool> visited, std::shared_ptr<std::ofstream> vis) {

}

