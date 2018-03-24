#ifndef CHAR_SET_H
#define CHAR_SET_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "char_range.h"

class char_set
{
private:
  std::map <char, bool> characters;
  std::vector<std::shared_ptr<char_range>> ranges;
public:
    char_set();
    char_set(char);
    char_set(const char_set&);
    void add_character(char);
    void add_range(char, char);

    // getters
    std::string get_string (char input);
    bool is_empty();
    const std::map <char, bool> &get_characters() const;
    const std::vector <std::shared_ptr<char_range>> &get_ranges() const;
};

#endif // CHAR_SET_H
