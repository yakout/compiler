#include <iostream>
#include "intermediate_code_generation/semantic_rules.h"
#include "predictive_parser.h"

void func1() {
    Label label = get_new_label();
}

int main (int argc, char *argv[]) {
    cfg_symbol symbol(ACTION);
    symbol.set_action(func1);
    symbol.get_action()();
}
