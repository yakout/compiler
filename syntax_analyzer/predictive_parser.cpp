#include "predictive_parser.h"

predictive_parser::predictive_parser (cfg_symbol start_symbol, std::shared_ptr<parsing_table> ll1_table, std::vector<std::string> lex_tokens)
	: input_buffer(lex_tokens), p_table(ll1_table), debug_stack(), output(), parser_stack()
{
	init_stack(start_symbol);
}

void predictive_parser::init_stack (cfg_symbol start_sym) 
{
    cfg_symbol end_marker(END_MARKER);
    parser_stack.push(end_marker);
    parser_stack.push(start_sym);
}

std::string predictive_parser::dump_stack () 
{
	std::stack<cfg_symbol> temp_stack;
	std::string stack_str = "";
	while (!parser_stack.empty())
	{
		temp_stack.push(parser_stack.top());
		stack_str += "(" + parser_stack.top().get_name() + ")";
        parser_stack.pop();
	}

	while (!temp_stack.empty())
	{
        parser_stack.push(temp_stack.top());
		temp_stack.pop();
	}

	return stack_str;
}


void predictive_parser::print_debug_stack () 
{
	for (std::string step : debug_stack)
	{
		std::cout << step << std::endl;
	}
}

std::vector<std::string> predictive_parser::get_debug_stack ()
{
	return debug_stack;
}

void predictive_parser::write_prod (cfg_production prod)
{
	output.push_back(prod.get_name());
}

void predictive_parser::write_derivations(std::string)
{

}

std::vector<std::string> predictive_parser::get_derivations ()
{
	return output;
}

void predictive_parser::handle_error()
{

}

void predictive_parser::parse() 
{
	int i = 0;
	while (!parser_stack.empty())
	{
		std::string cur_token = input_buffer[i];
		cfg_symbol stack_top = parser_stack.top();
		debug_stack.push_back(dump_stack());

		if (stack_top.get_type() == NON_TERMINAL)
		{
			cfg_production prod ;//= p_table->get_production(stack_top, cur_token);
			write_prod(prod);
			std::vector<cfg_symbol> symbols = prod.get_symbols();
			std::reverse(symbols.begin(), symbols.end());
			for (cfg_symbol sym : symbols)
			{
                parser_stack.push(sym);
			}
		}
		else if (stack_top.get_type() == TERMINAL)
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop();
				i++;
			}
			else
			{
				// TODO: ERROR!
			}
		}
		else if (stack_top.get_type() == END_MARKER)
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop();
				i++;
				break;
			}
		}
		else if (stack_top.get_type() == SYNCH)
		{
			if (cur_token == stack_top.get_name())
			{
                parser_stack.pop();
			}
		}
	}
}

