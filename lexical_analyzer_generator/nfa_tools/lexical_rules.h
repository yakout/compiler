#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "char_set.h"

#include <string>
#include <vector>

struct regular_definition
{
	std::string name;
	Char_Set sequence;
};

struct regular_expression // the production {NT -> (T|NT)+}
{
	std::string name;
	std::string rhs;
};

struct lexical_rules // set of rules (productions)
{
	std::vector <regular_definition> definitions;
	std::vector <regular_expression> expressions;
	std::vector <std::string> keywords;
	std::vector <char> punctuations;
};

#endif // GRAMMAR_H
