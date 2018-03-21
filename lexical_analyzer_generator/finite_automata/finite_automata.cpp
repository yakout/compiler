#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include "finite_automata.h"

fa::fa (std::shared_ptr<state> start, std::shared_ptr<state> acpt)
        : start_state(std::move(start)), acceptance_state(std::move(acpt))
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
                        "\tnode [shape = doublecircle]; "
                << acceptance_state->get_id() << ";\n"
                        "\tnode [shape = none] \"\";\n"
                        "\tnode [shape = circle];\n"
                        "\"\" -> " << start_state->get_id() << "\n";

    std::vector<bool> visited(6);
    dfs(start_state, visited, visualizer);

    *visualizer << "}\n";
    visualizer->close();
    exec("dot -Tpng -O fsm.dot");
}

