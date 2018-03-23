#include "char_range.h"

char_range::char_range(char lower, char upper) {
    lower_ascii = lower;
    upper_ascii = upper;
}

bool char_range::is_in_range(char c) {
    return c >= lower_ascii && c <= upper_ascii;
}

std::string char_range::get_range_string() {
    return std::string() + lower_ascii + "-" + upper_ascii;
}