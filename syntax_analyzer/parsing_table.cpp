#include "parsing_table.h"

parsing_table::parsing_table(cfg g)
{
    this->grammar = g;
    build ();
}

parsing_table::parsing_table(std::map<std::pair<std::string, std::string>, cfg_production> t)
    : table(t)
{

}

parsing_table::parsing_table() {}

std::shared_ptr<cfg_production> get_synch_prod ()
{
    cfg_symbol synch_symbol = cfg_symbol (SYNCH);
    std::vector <cfg_symbol> symbols; symbols.push_back(synch_symbol);
    cfg_production synch_prod = cfg_production (synch_symbol, symbols);
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
    std::unordered_map<std::string, std::vector<cfg_symbol>> first_set =
              first_cfg_set->get_set_map();
    std::unordered_map<std::string, std::vector<cfg_symbol>> follow_set =
              follow_cfg_set->get_set_map();
    for (auto non_terminal : non_terminals)
    {
        std::vector <cfg_symbol> first = first_set[non_terminal.get_name()];
        std::vector <cfg_symbol> follow = follow_set[non_terminal.get_name()];
        bool has_eps = false;
        cfg_symbol eps_terminal;
        // filling table with first symbols except for EPS case.
        for (auto first_terminal : first)
        {
            if (first_terminal.get_name() != EPS)
                table[make_pair(non_terminal.get_name(),first_terminal.get_name())]
                      = *first_terminal.get_parent_prod();
            else
            {
                eps_terminal = first_terminal;
                has_eps = true;
            }
        }
        if (has_eps)
        {
            for (auto follow_terminal : follow)
            {
                table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                      = *eps_terminal.get_parent_prod();
            }
        }
        else
        {
          cfg_production synch_prod = *get_synch_prod();
          for (auto follow_terminal : follow)
          {
              table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                    = synch_prod;
          }
        }
    }
}

cfg_production parsing_table::get_production (std::string rule, std::string token)
{
    return this->table[make_pair(rule, token)];
}
