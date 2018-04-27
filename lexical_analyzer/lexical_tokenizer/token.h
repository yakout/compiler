#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <string>

struct token {
    std::string lexeme;
    std::string token_class;
    int str_pos;
};

#endif //COMPILER_TOKEN_H
