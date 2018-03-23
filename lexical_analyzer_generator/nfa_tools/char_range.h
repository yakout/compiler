#ifndef CHAR_RANGE_H
#define CHAR_RANGE_H

#include <string>

class char_range
{
private:
  char lower_ascii;
  char upper_ascii;

public:
    explicit char_range(char, char);
    bool is_in_range (char c);
    std::string get_range_string ();
};

#endif // CHAR_RANGE_H
