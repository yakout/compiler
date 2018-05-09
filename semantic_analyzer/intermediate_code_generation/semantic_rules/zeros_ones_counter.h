#ifndef COMPILER_SEMANTIC_RULES_H
#define COMPILER_SEMANTIC_RULES_H

#include <iostream>
#include "../../../syntax_analyzer/context_free_grammar/cfg_symbol.h"

namespace zeros_ones_counter {

    int zeros = 0;
    int ones = 0;

    void record_A(std::vector<cfg_symbol> &stack) {
//                S{print A.n1, print A.n0}
        zeros = std::atoi(stack.back().get_attribute("n0").front().c_str());
        ones = std::atoi(stack.back().get_attribute("n1").front().c_str());

        std::cout << "number of zeros = " << zeros << std::endl;
        std::cout << "number of ones = " << ones << std::endl;
    }


    void record_B(std::vector<cfg_symbol> &stack) {
//                stack[top - 1].n0 = n0, stack[top - 1].n1 = n1
        stack[stack.size() - 2].add_attribute("n0", stack.back().get_attribute("n0").front());
        stack[stack.size() - 2].add_attribute("n1", stack.back().get_attribute("n1").front());
    }

    void record_B1_0(std::vector<cfg_symbol> &stack) {
//                S{[top - 1].n0 = B1.n0 + 1, [top - 1].n1 = B1.n1}
        stack[stack.size() - 2].
                add_attribute("n0", std::to_string(std::atoi(stack.back().get_attribute("n0").front().c_str()) + 1));
        stack[stack.size() - 2].add_attribute("n1", stack.back().get_attribute("n1").front());
    }

    void record_B1_1(std::vector<cfg_symbol> &stack) {
        stack[stack.size() - 2].
                add_attribute("n1", std::to_string(std::atoi(stack.back().get_attribute("n1").front().c_str()) + 1));
        stack[stack.size() - 2].add_attribute("n0", stack.back().get_attribute("n0").front());
    }


    void action_1(std::vector<cfg_symbol> &stack) {
//                @{[top - 1].n0 = 0, [top - 1].n1 = 0}
        stack[stack.size() - 2].add_attribute("n0", "0");
        stack[stack.size() - 2].add_attribute("n1", "0");
    }
}

#endif //COMPILER_SEMANTIC_RULES_H
