#include "char_set.h"
#include "../finite_automata/state.h"


Char_Range::Char_Range(char lower, char upper) {
    lower_ascii = lower;
    upper_ascii = upper;
}

bool Char_Range::is_in_range(char c) {
    return c >= lower_ascii && c <= upper_ascii;
}

std::string Char_Range::get_range_string() {
    return lower_ascii + "-" + upper_ascii;
}


std::string Char_Set::get_string(char input) {
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

Char_Set::Char_Set(): ranges(), characters() {

}

void Char_Set::add_character(char c) {
    characters[c] = true;
}

void Char_Set::add_range(char l, char u) {
    ranges.push_back(std::shared_ptr<Char_Range>(new Char_Range(l, u)));
}
