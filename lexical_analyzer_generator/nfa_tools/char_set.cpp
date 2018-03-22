#include "char_set.h"
#include "../finite_automata/state.h"


char_range::char_range(char lower, char upper) {
    lower_ascii = lower;
    upper_ascii = upper;
}

bool char_range::is_in_range(char c) {
    return c >= lower_ascii && c <= upper_ascii;
}

std::string char_range::get_range_string() {
    return lower_ascii + "-" + upper_ascii;
}


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



