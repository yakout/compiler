#include "lexical_rules.h"

Lexical_Rules::Lexical_Rules ()
{
}

void Lexical_Rules::add_punct_char (char punct)
{
  punctuations.push_back (punct);
}

void Lexical_Rules::add_keyword (std::string keyword)
{
  keywords.push_back (keyword);
}

void Lexical_Rules::add_reg_def (regular_definition definition)
{
  definitions.push_back (definition);
}

void Lexical_Rules::add_regex (regular_expression regex)
{
  expressions.push_back (regex);
}
