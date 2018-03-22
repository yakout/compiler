#include <iostream>
#include <fstream>
#include <array>
#include <utility>
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
    : start_state(), acceptance_states(), total_states(2) // TODO recheck this
{

}

std::string exec(const char* cmd) {
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

void fa::visualize() {
    std::shared_ptr<std::ofstream> visualizer(new std::ofstream());
    visualizer->open("fsm.dot");
    *visualizer <<
                "digraph finite_state_machine {\n"
                        "\trankdir=LR;\n"
                        "\tsize=\"8,5\"\n"
                        "\tnode [shape = doublecircle]; ";
    for (auto s : acceptance_states)
    {
        *visualizer << s->get_id() << " ";
    }
    *visualizer << ";\n"
            "\tnode [shape = none] \"\";\n"
            "\tnode [shape = circle];\n"
            "\"\" -> " << start_state->get_id() << "\n";


    std::vector<bool> visited(6);
    dfs(start_state, visited, visualizer, false);
    *visualizer << "}\n";
    visualizer->close();

    #ifdef __linux__
        exec("dot -Tpng -O fsm.dot");
    #elif _WIN32
        execl("\"C:\\\\Program Files (x86)\\\\Graphviz2.38\\\\bin\\\\dot\"", "-Tpng", "-o", "D:\\\\img.png" , "fsm.dot");
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

void fa::update_acceptance_states()
{
    std::vector<bool> visted(static_cast<unsigned long>(total_states));
    dfs(start_state, visted, nullptr, true);
}



