#ifndef LEXICAL_ANALYZER_GENERATOR_H
#define LEXICAL_ANALYZER_GENERATOR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

class lexical_analyzer_generator
{
    public:
      FILE* get_lexical_analyzer_file(std::string rules_file);
};

#endif // LEXICAL_ANALYZER_GENERATOR_H
