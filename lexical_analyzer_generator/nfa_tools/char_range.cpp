#include "char_range.h"

char_range::char_range(char l, char u)
{
    lower = l;
    upper = u;
}

char_range::char_range(const char_range & c_r): lower(c_r.get_lower()), upper(c_r.get_upper()){

}

bool char_range::is_in_range(char c)
{
    return c >= lower && c <= upper;
}

std::string char_range::get_range_string()
{
    return std::string() + lower + "-" + upper;
}

const char char_range::get_upper() const
{
    return upper;
}

const char char_range::get_lower() const
{
    return lower;
}

