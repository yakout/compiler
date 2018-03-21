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

class Lexical_Rules // set of rules (productions)
{
private:
	std::vector <regular_definition> definitions;
	std::vector <regular_expression> expressions;
	std::vector <std::string> keywords;
	std::vector <char> punctuations;
public:
	void add_punct_char (char punct);
	void add_keyword (std::string keyword);
	void add_regex (regular_expression regex);
	void add_reg_def (regular_definition definition);

};

#endif // GRAMMAR_H
