#ifndef CHAR_RANGE_H
#define CHAR_RANGE_H

#include <string>

class char_range
{
private:
  char lower;
  char upper;

public:
    explicit char_range(char, char);
    bool is_in_range (char c);
    std::string get_range_string ();
    char get_lower();
    char get_upper();
};

#endif // CHAR_RANGE_H
