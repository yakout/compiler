#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include "cfg_production.h"
#include "cfg_rule.h"
#include <vector>
#include <map>

/**
  Class first contains first of certain cfg_rule (NON_TERMINAL)
  tokens.
*/
class first {
private:
    /** A map containing the tokens corresponding to the
    cfg_production that defined it for a cfg_rule.*/
//    std::map <cfg_production, std::vector <std::string>> tokens;
public:
    /** This function returns vector of all tokens in the first
    of this cfg_production.
    @returns vector containing tokens
    */
    std::vector <std::string> get_first_tokens (cfg_production);
};

/**
  Class follow contains follow of certain cfg_rule (NON_TERMINAL)
  tokens.
*/
class follow {
private:
    /** A vector containing all tokens in the follow of a cfg_rule .*/
    std::vector <std::string> follow_tokens;
public:
  /** This function returns vector of all tokens in the follow
  of cfg_rule.
  @returns vector containing tokens
  */
    std::vector <std::string> get_follow_tokens();
};

/**
  This class contains first and follow for every cfg_rule (NON_TERMINAL) in a cfg.
.*/
class first_follow_sets {
private:
    /** A map containing pair of first and follow for every cfg_rule in a cfg.*/
//    std::map <cfg_rule, std::pair <first, follow>> first_follow_table;
public:
    /** This function returns first of a cfg_rule.
    @returns first of the cfg_rule
    */
    first get_first (cfg_rule);
    /** This function returns follow of a cfg_rule.
    @returns follow of the cfg_rule
    */
    follow get_follow (cfg_rule);
};

#endif // FIRST_FOLLOW_H
