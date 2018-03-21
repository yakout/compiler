#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <map>

class Char_Range
{
private:
  char lower_ascii;
  char upper_ascii;

public:
    explicit Char_Range(char, char);
    bool is_in_range (char c);
    std::string get_range_string ();
};

class Char_Set
{
private:
  std::map <char, bool> characters;
  std::vector <std::shared_ptr<Char_Range>> ranges;
public:
    Char_Set();
    void add_character(char);
    void add_range(char, char);
    std::string get_string (char input);

};

#endif // INPUT_H
