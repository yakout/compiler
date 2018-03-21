#ifndef LEXICAL_ANALYZER_GENERATOR_H
#define LEXICAL_ANALYZER_GENERATOR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
 

class Lexical_Analyzer_Generator
{
    public:
      FILE* get_lexical_analyzer_file(std::string rules_file);
};

#endif // LEXICAL_ANALYZER_GENERATOR_H
