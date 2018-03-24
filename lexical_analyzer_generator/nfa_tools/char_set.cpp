#include "char_set.h"
#include "../finite_automata/state.h"

std::string char_set::get_string(char input) {
    if (characters.count(input) != 0) {
        return std::string("") + input;
    }
    for (auto range : ranges) {
        if (range->is_in_range(input)) {
            return range->get_range_string();
        }
    }

    return EPSILON; // empty char_set i.e epsilon transition
}

char_set::char_set(): ranges(), characters() {

}

char_set::char_set(char c) : ranges(), characters()
{
  characters[c] = true;
}

char_set::char_set(const char_set & c_s)
        : ranges(), characters(c_s.get_characters())
{
    for (auto const& r : c_s.get_ranges())
    {
        ranges.push_back(std::shared_ptr<char_range>(new char_range(*r)));
    }
}

void char_set::add_character(char c) {
    characters[c] = true;
}

void char_set::add_range(char l, char u) {
    ranges.push_back(std::shared_ptr<char_range>(new char_range(l, u)));
}

const std::map <char, bool> &char_set::get_characters() const
{
    return characters;
}

const std::vector <std::shared_ptr<char_range>> &char_set::get_ranges() const
{
    return ranges;
}

bool char_set::is_empty() {
    return characters.empty() && ranges.empty();
}
