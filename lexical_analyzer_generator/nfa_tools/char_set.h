#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <map>

class Char_Range
{
private:
  int lower_ascii;
  int upper_ascii;

public:
  bool is_in_range (char c);
};

class Char_Set
{
private:
  std::map <char, bool> characters;
  std::vector <Char_Range> ranges;
public:
  std::string get_string (char input);
};

#endif // INPUT_H
