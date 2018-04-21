#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H
#include "cfg_production.h"
#include "cfg_rule.h"
#include <vector>
#include <map>

class first {
private:
    std::map <cfg_production, std::vector <char>> tokens;
public:
    std::vector <char> get_first_tokens (cfg_production);
};

class follow {
private:
    std::vector <char> follow_tokens;
public:
    std::vector <char> get_follow_tokens();
};

class first_follow_sets {
private:
    std::map <cfg_rule, std::pair <first, follow>> first_follow_table;
public:
    first get_first (cfg_rule);
    follow get_follow (cfg_rule);
};

#endif // FIRST_FOLLOW_H
