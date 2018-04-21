#ifndef COMPILER_PARSING_TABLE_H
#define COMPILER_PARSING_TABLE_H

#include "cfg.h"
#include "first_follow.h"

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
    first_follow_sets first_follow;
    /** Parsing Table accessed by rule (NON_TERMINAL) and string (TOKEN) to
       get cfg_production used or error.*/
    std::map <std::pair<cfg_rule, std::string>, cfg_production> table;

    /**
        This function builds the parsing table for the previously defined grammar.
        It fills the table map defined above by productions using the first and.
        follow sets supplied before.
    */
    void build();
public:
    /**
        Contructor for parsing table.
        @param cfg grammar to build parsing table for
        @param first_follow_sets to be used in building parsing table
    */
    parsing_table (cfg, first_follow_sets);
    /**
        Default Contructor for parsing table.
    */
    parsing_table ();
};



#endif //COMPILER_PARSING_TABLE_H
