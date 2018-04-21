#include "parsing_table.h"

parsing_table::parsing_table(cfg g, first_follow_sets ff)
        : grammar(g), first_follow(ff), table()
{

}

parsing_table::parsing_table()
{

}

bool parsing_table::fill_entries (cfg_production production, std::shared_ptr<cfg_rule> rule,
                    std::vector<std::string> tokens)
{
    for (std::string token : tokens)
    {
        table[{rule, token}] = production;
    }
}


void parsing_table::build() 
{
    for (cfg_rule rule_obj : grammar.get_rules())
    {
        std::shared_ptr<cfg_rule> rule = std::make_shared<cfg_rule> (rule_obj); // TODO :: WRONG
        first first_set = first_follow.get_first (*rule);
        follow follow_set = first_follow.get_follow (*rule);
        bool eps_found = false; // to check whether this rule has epsilon production.
        for (cfg_production production : rule->get_productions())
        {
            std::vector<cfg_symbol> symbols = production.get_symbols();
            if (symbols.size() == 1 and symbols[0].get_type() == END_MARKER)
            {
                eps_found = true;
                fill_entries (production, rule, follow_set.get_follow_tokens());
            }
            else
            {
              fill_entries (production, rule, first_set.get_first_tokens(production));
            }
        }
        cfg_production sync_prod;     // TODO : initialize sync_prod correctly
        if (!eps_found)
        {
            fill_entries (sync_prod, rule, follow_set.get_follow_tokens());
        }
    }
}

cfg_production parsing_table::get_production (std::shared_ptr<cfg_rule> rule, std::string token)
{
    return this->table[{rule, token}];
}
