#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

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

class char_set
{
private:
  std::map <char, bool> characters;
  std::vector <std::shared_ptr<char_range>> ranges;
public:
    char_set();
    void add_character(char);
    void add_range(char, char);

    // getters
    std::string get_string (char input);

    const std::map <char, bool> &get_characters() const;
    const std::vector <std::shared_ptr<char_range>> &get_ranges() const;
};

#endif // INPUT_H
