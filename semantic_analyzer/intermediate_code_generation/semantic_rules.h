#ifndef COMPILER_SEMANTIC_RULES_H
#define COMPILER_SEMANTIC_RULES_H

#include <iostream>

int label_counter = 0;

std::string get_new_label() {
    return std::to_string(label_counter++);
}

void func1() {
    std::string l1 = get_new_label();
    std::string l2 = get_new_label();

    std::cout << l1 << " " << l2 << std::endl;
}

#endif //COMPILER_SEMANTIC_RULES_H
