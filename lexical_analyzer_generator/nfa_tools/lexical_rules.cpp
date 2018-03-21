#include "lexical_rules.h"

lexical_rules::lexical_rules ()
{
}

void lexical_rules::add_punct_char (char punct)
{
  punctuations.push_back (punct);
}

void lexical_rules::add_keyword (std::string keyword)
{
  keywords.push_back (keyword);
}

void lexical_rules::add_reg_def (regular_definition definition)
{
  definitions.push_back (definition);
}

void lexical_rules::add_regex (regular_expression regex)
{
  expressions.push_back (regex);
}
