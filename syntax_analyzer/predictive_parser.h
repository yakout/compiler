#ifndef COMPILER_PREDICTIVE_PARSER_H
#define COMPILER_PREDICTIVE_PARSER_H

#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include "parsing_table.h"
#include "cfg_production.h"

class predictive_parser
{
private:
    std::stack<cfg_symbol> parser_stack;
    std::vector<std::string> debug_stack; // used for debugging
    std::vector<std::string> input_buffer;
    std::vector<std::string> output;
    std::shared_ptr<parsing_table> p_table;
    /**
     * Writes the action taken in each step (derivation steps) into the output vector.
     */
    void write_prod (cfg_production prod);
    /**
     * Initialize the stack with the end marker ($) and the start symbol.
     */
    void init_stack (cfg_symbol);
    /**
     * converts the current stack contents into string.
     */
    std::string dump_stack();
    /**
     * // TODO
     */
    void handle_error();
public:
    /**
     * Takes the start_symbol, parsing table, and the input buffer to be parsed.
     * 
     * @param input_buffer the sequence of tokens produced from lexical analyzer.
     *  // TODO change the input_buffer to lexical class and call get_next_token() function on it, rather 
     *  than fetching all the source code tokens into memory.
     * 
     * @param start_symbol grammer's start symbol
     * @param p_table The parsing table constructed from the context free grammer production rules.
     * 
     */ 
    predictive_parser (cfg_symbol start_symbol, std::shared_ptr<parsing_table> p_table, std::vector<std::string> input_buffer);
    /**
     * print the debug stack contents into consol for debugging.
     */
    void print_debug_stack ();
    /**
     * returns the debug stack.
     */ 
    std::vector<std::string> get_debug_stack ();
    /**
     * returns the derivations steps.
     */
    std::vector<std::string> get_derivations ();
    /**
     * writes the derivations steps into output file.
     */ 
    void write_derivations (std::string);
    /**
     * 
     */
    void parse();
};

#endif //COMPILER_PREDICTIVE_PARSER_H