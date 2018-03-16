#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>

struct prod_t // the production {NT -> (T|NT)+}
{
	std::string lhs;
  std::string rhs;
};

struct grammer_t // set of rules (productions)
{
	std::vector<prod_t> rules;
};



#endif // GRAMMAR_H
