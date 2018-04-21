#include "parsing_table.h"

parsing_table::parsing_table(cfg grammar, first_follow_sets first_follow) {
    this->grammar = grammar;
    this->first_follow = first_follow;
}

parsing_table::parsing_table() {}


void parsing_table::build() {
    for (cfg_rule rule_obj : grammar.get_rules())
    {
        std::shared_ptr<cfg_rule> rule = std::make_shared<cfg_rule> (rule_obj); // TODO :: WRONG
        first first_set = first_follow.get_first (*rule);
        follow follow_set = first_follow.get_follow (*rule);
        bool eps_found = false;

        for (cfg_production production : rule->get_productions())
        {
            std::vector<cfg_symbol> symbols = production.get_symbols();
            if (symbols.size() == 1 and symbols[0].get_type() == END_MARKER)
            {
                eps_found = true;
                for (std::string token : follow_set.get_follow_tokens())
                {
                    table[{rule, token}] = production;
                }
            }
            else
            {
              for (std::string token : first_set.get_first_tokens(production))
              {
                  table[{rule, token}] = production;
              }
            }
        }
        cfg_production sync_prod;
        if (!eps_found)
        {
            for (std::string token : follow_set.get_follow_tokens())
            {
                table[{rule, token}] = sync_prod;
            }
        }
    }
}

cfg_production parsing_table::get_production (std::shared_ptr<cfg_rule> rule, std::string token)
{
    return this->table[{rule, token}];
}
