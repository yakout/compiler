#ifndef SYNTAX_ANALYZER_UTIL_H
#define SYNTAX_ANALYZER_UTIL_H

#include <vector>
#include <string>

namespace syntax_util
{
    void split_str_on_space (std::vector<std::string> &vec,
                            std::string &str, char c);

    void remove_quotes (std::string &str);

}

#endif // SYNTAX_ANALYZER_UTIL_H
