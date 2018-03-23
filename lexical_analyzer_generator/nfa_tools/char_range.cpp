#include "char_range.h"

char_range::char_range(char l, char u) {
    lower = l;
    upper = u;
}

bool char_range::is_in_range(char c) {
    return c >= lower && c <= upper;
}

std::string char_range::get_range_string() {
    return std::string() + lower + "-" + upper;
}

char char_range::get_upper() {
    return upper;
}

char char_range::get_lower() {
    return lower;
}
