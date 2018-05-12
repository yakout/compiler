#include "predictive_parser.h"

predictive_parser::predictive_parser (cfg_symbol start_symbol, std::shared_ptr<parsing_table> ll1_table,
									  std::vector<std::string> lex_tokens)
	: input_buffer(lex_tokens), p_table(ll1_table), debug_stack(), output(), parser_stack()
{
	errors_count = 0;
	init_stack(start_symbol);
}

predictive_parser::predictive_parser (cfg_symbol start_symbol, std::shared_ptr<parsing_table> ll1_table,
									  std::vector<token> token_vec)
		: p_table(ll1_table), debug_stack(), output(), parser_stack()
{
	errors_count = 0;
	init_stack(start_symbol);

	for (auto tok : token_vec)
	{
		input_buffer.push_back(tok.token_class);
		lex_values.push_back(tok.lexeme);
	}

}

predictive_parser::predictive_parser(char *cfg_file, std::vector<token> token_vec)
{
	errors_count = 0;
    for (auto tok : token_vec)
    {
        input_buffer.push_back(tok.token_class);
    }
	input_buffer.push_back("$");

    cfg grammar(cfg_file);

    grammar.left_factor();
    grammar.remove_left_recursion();

    std::shared_ptr<parsing_table> ll1_table = std::make_shared<parsing_table>(grammar);
    p_table = ll1_table;
    init_stack(grammar.get_start_symbol());
}

void predictive_parser::init_stack (cfg_symbol start_sym) 
{
    cfg_symbol end_marker("$", END_MARKER);
    parser_stack.push_back(end_marker);
    parser_stack.push_back(start_sym);
}

std::string predictive_parser::dump_stack () 
{
	std::stack<cfg_symbol> temp_stack;
	std::string stack_str = "";
	while (!parser_stack.empty())
	{
        if (parser_stack.back().get_name() != "$") {
            stack_str += parser_stack.back().get_name() + " ";
        }
        temp_stack.push(parser_stack.back());
        parser_stack.pop_back();
	}

	while (!temp_stack.empty())
	{
        parser_stack.push_back(temp_stack.top());
		temp_stack.pop();
	}

	return stack_str;
}

std::vector<std::string> predictive_parser::get_debug_stack ()
{
	return debug_stack;
}

void predictive_parser::write_prod (cfg_production prod)
{
	output.push_back (prod.to_string());
}


std::vector<std::string> predictive_parser::get_derivations ()
{
	return output;
}

int predictive_parser::parse() 
{
	int i = 0;
	while (!parser_stack.empty())
	{
		std::string cur_token = input_buffer[i];
		cfg_symbol stack_top = parser_stack.back();
		debug_stack.push_back(dump_stack());

		if (stack_top.get_type() == NON_TERMINAL)
		{
			cfg_production prod = p_table->get_production(stack_top.get_name(), cur_token);
            if (prod.get_lhs_symbol().get_type() == SYNCH)
            {
                parser_stack.pop_back();
                output.push_back("SYNCH (pop_stack)");
            }
            else if (prod.get_symbols().empty())
            {
                // ERROR! discard curr_tok
                if (cur_token == "$") {
                    output.push_back("END! Error: (illegal " + stack_top.get_name() + ") - discard " + cur_token);
                    errors_count++;
                    break;
                }
                output.push_back("Error: (illegal " + stack_top.get_name() + ") - discard " + cur_token);
                errors_count++;
                i++;
            }
            else
            {
                write_prod(prod);
                std::vector<cfg_symbol> symbols = prod.get_symbols();
                std::reverse(symbols.begin(), symbols.end());

                if (prod.get_symbols().front().get_name() != EPS)
                {
                    bool flag = parser_stack.back().has_inherited_attribute();
                    std::map<std::string, std::vector<std::string>> inh_attr;
                    if (flag) {
                        inh_attr = parser_stack.back().get_inherited_attributes();
                    }

                    parser_stack.pop_back();
                    for (cfg_symbol sym : symbols) {
                        parser_stack.push_back(sym);
                    }

                    if (flag) {
                        parser_stack.back().set_inherited_attributes(inh_attr);
                    }
                }
                else if (prod.get_symbols().front().get_name() == EPS && prod.get_symbols().size() > 1)
                {
                    // ACTIONS AND SYNTHESISED ATTRIBUTES.
                    parser_stack.pop_back();
                    for (int j = 0; j < symbols.size() - 1; ++j) {
                        parser_stack.push_back(symbols[j]);
                    }
                }
                else
                {
                    // EPSILON PRODUCTION
                    parser_stack.pop_back();
                }
            }
		}
		else if (stack_top.get_type() == TERMINAL)
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop_back();
                output.push_back("match: " + cur_token);
				if (!parser_stack.empty() && i < lex_values.size()) {
					parser_stack.back().add_attribute("lexval", lex_values[i]);
				}
				i++;
			}
			else
			{
                // ERROR! insert curr_tok
                output.push_back("Error: (missing " + stack_top.get_name() + ") - inserted.");
                errors_count++;
                parser_stack.pop_back();
			}
		}
		else if (stack_top.get_type() == END_MARKER)
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop_back();
				output.push_back("accept");
				break;
			} else {
                output.push_back("Error: (illegal " + stack_top.get_name() + " - discard " + cur_token);
                errors_count++;
                i++;
            }
		}
		else if (stack_top.get_type() == SYNCH) // TODO this will never happen
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop_back();
			}
		}
		else if (stack_top.get_type() == ACTION)
		{
			stack_top.get_action()(parser_stack);
            parser_stack.pop_back();
		}
		else if (stack_top.get_type() == SYNTHESISED)
		{
			stack_top.get_action()(parser_stack);
            parser_stack.pop_back();
		}
	}
	return errors_count;
}

void predictive_parser::write_debug_stack(std::string file_name)
{
	std::ofstream output_file;
	output_file.open(file_name);

	for (auto s : debug_stack)
	{
		output_file << s << std::endl;
	}
	output_file.close();
}

void predictive_parser::write_derivations(std::string file_name)
{
	std::ofstream output_file;
	output_file.open(file_name);

	for (auto derivation : output)
	{
		output_file << derivation << std::endl;
	}

	output_file.close();
}
