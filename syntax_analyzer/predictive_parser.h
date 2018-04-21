#ifndef COMPILER_PREDICTIVE_PARSER_H
#define COMPILER_PREDICTIVE_PARSER_H

#include <stack>
#include <string>
#include <vector>
#include "parsing_table.h"
#include "cfg_production.h"

class predictive_parser
{

private:
    std::stack<std::string> stack;
    std::stack<std::string> debug_stack; // used for debugging
    std::string input_buffer;
    parsing_table p_table;
    std::vector<std::string> output;

public:
    predictive_parser();
    void init_stack();
    void print_stack();
    void write_prod(cfg_production prod);

};

#endif //COMPILER_PREDICTIVE_PARSER_H