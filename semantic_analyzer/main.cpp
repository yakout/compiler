#include <iostream>
#include "intermediate_code_generation/semantic_rules.h"
#include "../syntax_analyzer/context_free_grammar/cfg_symbol.h"


int main (int argc, char *argv[]) {
    cfg_symbol symbol(ACTION);
    symbol.set_action(func1);
    symbol.get_action()();
}
