#ifndef COMPILER_PARSING_TABLE_H
#define COMPILER_PARSING_TABLE_H

#include "context_free_grammar/cfg.h"
#include "context_free_grammar/cfg_symbol.h"
#include "context_free_grammar/cfg_rule.h"

#include <map>

/**
    Parsing table that contains state machine to parse input program.
*/
class parsing_table
{
private:
    /** Grammar that the parsing table represents.*/
    cfg grammar;
    /** First and Follow sets for the grammar above.*/
//    first_follow_sets first_follow;
    /** Parsing Table accessed by rule (NON_TERMINAL) and string (TOKEN) to
       get cfg_production used or error.*/
    std::map <std::pair<std::string, std::string>, cfg_production> table;

      /**
        This function builds the parsing table for the previously defined grammar.
        It fills the table map defined above by productions using the first and.
        follow sets supplied before.
    */
    void build();
public:
    /**
     *  Constructor for parsing table.
     *  @param cfg grammar to build parsing table for
     *  @param first_follow_sets to be used in building parsing table
     */
    parsing_table (cfg);

    /**
     * Constructor for parsing table, that takes the map with the productions entries in it.
     * used for testing.
     */
    parsing_table (std::map <std::pair<std::string, std::string>, cfg_production> table);

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
};



#endif //COMPILER_PARSING_TABLE_H
