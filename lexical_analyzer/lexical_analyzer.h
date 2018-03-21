#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <stdio.h>
#include "token.h"

class Lexical_Analyzer
{
private:
  FILE* lexical_analyzer_machine;
  FILE* code_file;
public:
  Lexical_Analyzer (FILE* lexical_analyzer, FILE* file);
  token get_next_token ();
};

#endif // LEXICAL_ANALYZER_H
