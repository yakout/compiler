#include "parsing_table.h"

#include "context_free_grammar/synch_production.h"

parsing_table::parsing_table(cfg g)
 : grammar(g)
{
    build ();
}

parsing_table::parsing_table(std::map<std::pair<std::string, std::string>, cfg_production> t)
    : table(t)
{

}

parsing_table::parsing_table() {}

std::shared_ptr<cfg_production> get_synch_prod ()
{
    synch_production synch_prod = synch_production ();
    std::shared_ptr<cfg_production> prod =
                    std::make_shared<cfg_production> (synch_prod);
    return prod;
}



void parsing_table::build()
{
   /// list of non-terminals in the CFG.
   std::vector <cfg_symbol> non_terminals = grammar.get_non_terminals ();
   /// First and follow cfg_sets
   std::shared_ptr <cfg_set> first_cfg_set = grammar.get_first_set();
   std::shared_ptr <cfg_set> follow_cfg_set = grammar.get_follow_set();
   /// First and Follow maps.
   std::unordered_map<std::string, std::vector<std::pair<cfg_symbol,
                      std::shared_ptr<cfg_production>>>> first_set =
             first_cfg_set->get_set_map();
   std::unordered_map<std::string, std::vector<std::pair<cfg_symbol,
                      std::shared_ptr<cfg_production>>>> follow_set =
             follow_cfg_set->get_set_map();
   for (auto non_terminal : non_terminals)
   {
      std::vector<std::pair<cfg_symbol,
                  std::shared_ptr<cfg_production>>> first = first_set[non_terminal.get_name()];
      std::vector<std::pair<cfg_symbol,
                  std::shared_ptr<cfg_production>>> follow = follow_set[non_terminal.get_name()];
       bool has_eps = false;
       cfg_symbol eps_terminal;
       std::shared_ptr <cfg_production> eps_prod;
       // filling table with first symbols except for EPS case.
       for (auto first_terminal : first)
       {
           if (first_terminal.first.get_name() != EPS)
               table[make_pair(non_terminal.get_name(), first_terminal.first.get_name())]
                     = *first_terminal.second;
           else
           {
               eps_terminal = first_terminal.first;
               eps_prod = first_terminal.second;
               has_eps = true;
           }
       }
       if (has_eps)       /// case of eps production in the rule.
       {
           for (auto follow_terminal : follow) /// add eps production to follow entries in table
           {
               table[make_pair(non_terminal.get_name(), follow_terminal.first.get_name())]
                     = *eps_prod;
           }
       }
       else
       {
         cfg_production synch_prod = *get_synch_prod();
         for (auto follow_terminal : follow)
         {
             table[make_pair(non_terminal.get_name(), follow_terminal.first.get_name())]
                   = synch_prod;
         }
       }
   }
}

cfg_production parsing_table::get_production (std::string rule, std::string token)
{
    return table[make_pair(rule, token)];
}
