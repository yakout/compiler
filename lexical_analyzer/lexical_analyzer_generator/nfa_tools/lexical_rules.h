#ifndef LEXICAL_RULES_H
#define LEXICAL_RULES_H

#include "char_set.h"

#include <string>
#include <vector>

struct regular_definition
{
	std::string name;
	char_set sequence;
};

struct regular_expression
{
	std::string name;
	std::string rhs;
};

class lexical_rules
{
private:
	std::vector <regular_definition> definitions;
	std::vector <regular_expression> expressions;
	std::vector <std::string> keywords;
	std::vector <char> punctuations;
public:
	lexical_rules ();
	void add_punct_char (char punct);
	void add_keyword (std::string keyword);
	void add_regex (regular_expression regex);
	void add_reg_def (regular_definition definition);

};

#endif // LEXICAL_RULES_H
