#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

typedef std::string token_t;

struct token
{
	token_t type;
	std::vector<std::string> lexem; // token can be associated with one lexeme (e.g '<') or multiple lexems (e.g 123725).
	std::string attr_value; // need more info
	//position_t pos; // position in source program, will help in error report
};


#endif // TOKEN_H
