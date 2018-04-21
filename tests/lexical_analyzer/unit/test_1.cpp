#include "../../lib/catch.hpp"
#include "../../../lexical_analyzer/lexical_analyzer_generator/nfa_tools/regex_processor.h"

TEST_CASE("test regex_processor")
{
     std::map <std::string,std::shared_ptr<nfa>> sym_table;
     regular_expression regex1 = {"letter", "a-z | A-Z"};
     std::shared_ptr<nfa> letter_nfa = evaluate_regex (regex1, sym_table);
     REQUIRE(letter_nfa->get_start_state()->get_id() == 0);
}


TEST_CASE("dummy test")
{
    REQUIRE(1+1-2 == 0);
}