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
    explicit char_range(const char_range&);
    bool is_in_range (char c);
    std::string get_range_string ();
    const char get_lower() const ;
    const char get_upper() const ;
};

#endif // CHAR_RANGE_H
