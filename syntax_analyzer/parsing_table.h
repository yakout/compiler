#ifndef COMPILER_PARSING_TABLE_H
#define COMPILER_PARSING_TABLE_H

#include "context_free_grammar/cfg.h"
#include "context_free_grammar/cfg_symbol.h"
#include "context_free_grammar/cfg_rule.h"

#include <unordered_map>
#include <set>
#include <iomanip>
#include <iostream>
#include <fstream>

/**
    Parsing table that contains state machine to parse input program.
*/

struct parsing_table_comparator {
    bool operator()(const std::pair<std::string, std::string> &p1,
                    const std::pair<std::string, std::string> &p2) const {
        if (!p1.first.compare (p2.first) && p1.second == p2.second)
            return true;
        return false;
    }
};

struct parsing_table_hasher {
    std::size_t operator()(const std::pair<std::string, std::string> &p) const {
        return std::hash<std::string>()(p.first) ^ std::hash<std::string>()(p.second);
    }
};

class parsing_table
{
private:
    /** Grammar that the parsing table represents.*/
    cfg grammar;
    /** First and Follow sets for the grammar above.*/
//    first_follow_sets first_follow;
    /** Parsing Table accessed by rule (NON_TERMINAL) and string (TOKEN) to
       get cfg_production used or error.*/
    std::unordered_map <std::pair<std::string, std::string>, cfg_production,
            parsing_table_hasher, parsing_table_comparator> table;

    /**
     *  This function builds the parsing table for the previously defined grammar.
     *   It fills the table map defined above by productions using the first and.
     *   follow sets supplied before.
     */
    void build(first_set, follow_set);

    /**
     * This function builds the parsing table for the previously defined grammar.
     */
    void build();
public:
    /**
     *  Constructor for parsing table.
     *  @param cfg grammar to build parsing table for
     *  @param first_follow_sets to be used in building parsing table
     */
    parsing_table (cfg);
    parsing_table (cfg, first_set, follow_set);
    /**
     * Constructor for parsing table, that takes the map with the productions entries in it.
     * used for testing.
     */
    parsing_table (std::unordered_map <std::pair<std::string, std::string>, cfg_production,
            parsing_table_hasher, parsing_table_comparator> table);
    /**
     * Default Contructor for parsing table.
     */
    parsing_table ();
    /**
     *
     * This function returns the production corresponding to the given cfg_rule.
     * (NON_TERMINAL) and given string (TOKEN) from the parsing table.
     * @returns cfg_production or NULL if none found to denote Error
     *
     */
    cfg_production get_production (std::string, std::string);
    /**
     * draw the parsing table into given file name.
     */
    void draw(std::string file_name);
};



#endif //COMPILER_PARSING_TABLE_H
