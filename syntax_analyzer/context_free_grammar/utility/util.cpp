#include "util.h"

#include <sstream>
#include <algorithm>

#define QUOTES '\''

void split_str_on_space (std::vector<std::string> &vec,
                          std::string &str, char delimiter) {
    std::stringstream ss_str (str);
    std::string token;
    while (getline (ss_str, token, delimiter)) {
        vec.push_back(token);
    }
    return;
}

void remove_quotes (std::string &str) {
    if (str.length () > 2) {
        str.erase (remove (str.begin (), str.end (), '\''), str.end ());
        str.erase (remove (str.begin (), str.end (), '\''), str.end ());
    }
    return;
}
