#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include "finite_automata.h"

fa::fa(std::shared_ptr<state> start_state, std::vector<std::shared_ptr<state>> acceptance_states, int total_states) {
    fa::start_state = std::move(start_state);
    fa::acceptance_states = std::move(acceptance_states);
    fa::total_states = total_states;
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
    dfs(start_state, visited, visualizer);
    *visualizer << "}\n";
    visualizer->close();

    #ifdef __linux__
        exec("dot -Tpng -O fsm.dot");
    #elif _WIN32
        execl("\"C:\\\\Program Files (x86)\\\\Graphviz2.38\\\\bin\\\\dot\"", "-Tpng", "-o", "D:\\\\img.png" , "fsm.dot");
    #else
        exec("dot -Tpng -O fsm.dot");
    #endif
}

const std::shared_ptr<state> &fa::get_start_state() const {
    return start_state;
}

const std::vector<std::shared_ptr<state>> &fa::getAcceptance_states() const {
    return acceptance_states;
}

int fa::getTotal_states() const {
    return total_states;
}

