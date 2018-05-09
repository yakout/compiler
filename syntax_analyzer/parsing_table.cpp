#include "parsing_table.h"

#define INVALID_LL1_GRAMMAR "This is NOT LL1 Grammar"

parsing_table::parsing_table(cfg g)
        : grammar(g), table()
{
    build ();
}

parsing_table::parsing_table(cfg g, first_set first, follow_set follow)
 : grammar(g), table()
{
    build (first, follow);
}

parsing_table::parsing_table(std::unordered_map <std::pair<std::string, std::string>, cfg_production,
        parsing_table_hasher, parsing_table_comparator> t)
    : table(t), grammar()
{

}

parsing_table::parsing_table() {}

std::shared_ptr<cfg_production> get_synch_prod ()
{
    // TODO
    std::vector<cfg_symbol> v;
    cfg_symbol synch(SYNCH);
    cfg_production synch_prod(synch, v);

    std::shared_ptr<cfg_production> prod =
                    std::make_shared<cfg_production> (synch_prod);
    return prod;
}

void parsing_table::build()
{
   /// list of non-terminals in the CFG.
   std::unordered_set <cfg_symbol, cfg_symbol::hasher
                , cfg_symbol::comparator> non_terminals = grammar.get_non_terminals ();
   /// First and follow cfg_sets
   std::shared_ptr <first_set> first_cfg_set = grammar.get_first_set();
   std::shared_ptr <follow_set> follow_cfg_set = grammar.get_follow_set();
   /// First and Follow maps.
   auto first_set = first_cfg_set->get_set_map();
   auto follow_set = follow_cfg_set->get_set_map();
   for (auto non_terminal : non_terminals)
   {
//      std::cout << "Non-Terminal : " << non_terminal.get_name() << std::endl;
      auto first = first_set[non_terminal.get_name()];
      auto follow = follow_set[non_terminal.get_name()];
       bool has_eps = false;
       cfg_symbol eps_terminal;
       cfg_production *eps_prod;
//       for (auto first_terminal : first) std::cout << first_terminal.first.get_name() << std::endl;
       // filling table with first symbols except for EPS case.
       for (auto first_terminal : first)
       {
           auto it = table.find(std::make_pair(non_terminal.get_name(),
                                          first_terminal.first.get_name()));

//           std::cout << "\tAttempting Adding Entry : {" <<
//           non_terminal.get_name() << " , " <<
//           first_terminal.first.get_name() << '}' << std::endl;

           if (first_terminal.first.get_name() != EPS && it == table.end())
           {
//              std::cout << "\tAdding to table" << std::endl;
              // table.insert (std::pair <std::pair<std::string, std::string>, cfg_production>(make_pair(non_terminal.get_name(), first_terminal.first.get_name()),synch_prod));
              table[std::make_pair(non_terminal.get_name(), first_terminal.first.get_name())]
                  = *first_terminal.second;
           }
           else if (first_terminal.first.get_name() == EPS)
           {
               eps_terminal = first_terminal.first;
               eps_prod = first_terminal.second;
               has_eps = true;
           }
           else
           {
                throw std::runtime_error(INVALID_LL1_GRAMMAR);
           }

       }
       if (has_eps)       /// case of eps production in the rule.
       {
           for (auto follow_terminal : follow) /// add eps production to follow entries in table
           {
               auto it = table.find(std::make_pair(non_terminal.get_name(),
                                                   follow_terminal.get_name()));
               if (it == table.end()) {
                   table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                           = *eps_prod;
               } else {
//                   std::cout << "\n\nnonterminal: " << non_terminal.get_name() << std::endl;
//                   std::cout << "old: " << table[make_pair(non_terminal.get_name(), follow_terminal.get_name())].to_string()
//                             << std::endl;
//                   table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
//                           = *eps_prod;
//
//                   std::cout << "new: " << table[make_pair(non_terminal.get_name(), follow_terminal.get_name())].to_string()
//                             << std::endl;
                    throw std::runtime_error(INVALID_LL1_GRAMMAR);
               }
           }
       }
       else
       {
         cfg_production synch_prod = *get_synch_prod();
         for (auto follow_terminal : follow)
         {
             auto it = table.find(make_pair(non_terminal.get_name(), follow_terminal.get_name()));
             if (it == table.end()) {
                 table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                         = synch_prod;
             }
         }
       }
   }
}


void parsing_table::build(first_set first_set1, follow_set follow_set1)
{
    /// list of non-terminals in the CFG.
    std::unordered_set <cfg_symbol, cfg_symbol::hasher
            , cfg_symbol::comparator> non_terminals = grammar.get_non_terminals ();
    /// First and follow cfg_sets
    std::shared_ptr <first_set> first_cfg_set = grammar.get_first_set();
    std::shared_ptr <follow_set> follow_cfg_set = grammar.get_follow_set();
    /// First and Follow maps.
//   auto first_set = first_cfg_set->get_set_map();
//   auto follow_set = follow_cfg_set->get_set_map();
    auto first_set = first_set1.get_set_map();
    auto follow_set = follow_set1.get_set_map();
    for (auto non_terminal : non_terminals)
    {
//        std::cout << "Non-Terminal : " << non_terminal.get_name() << std::endl;
        auto first = first_set[non_terminal.get_name()];
        auto follow = follow_set[non_terminal.get_name()];
        bool has_eps = false;
        cfg_symbol eps_terminal;
        cfg_production *eps_prod;
//        for (auto first_terminal : first) std::cout << first_terminal.first.get_name() << std::endl;
        // filling table with first symbols except for EPS case.
        for (auto first_terminal : first)
        {
            auto it = table.find(std::make_pair(non_terminal.get_name(),
                                                first_terminal.first.get_name()));

//            std::cout << "\tAttempting Adding Entry : {" <<
//                      non_terminal.get_name() << " , " <<
//                      first_terminal.first.get_name() << '}' << std::endl;

            if (first_terminal.first.get_name() != EPS && it == table.end())
            {
//                std::cout << "\tAdding to table" << std::endl;
                // table.insert (std::pair <std::pair<std::string, std::string>, cfg_production>(make_pair(non_terminal.get_name(), first_terminal.first.get_name()),synch_prod));
                table[std::make_pair(non_terminal.get_name(), first_terminal.first.get_name())]
                        = *first_terminal.second;
            }
            else if (first_terminal.first.get_name() == EPS)
            {
                eps_terminal = first_terminal.first;
                eps_prod = first_terminal.second;
                has_eps = true;
            }
            else
            {
                throw std::runtime_error(INVALID_LL1_GRAMMAR);

            }

        }
        if (has_eps)       /// case of eps production in the rule.
        {
            for (auto follow_terminal : follow) /// add eps production to follow entries in table
            {
                auto it = table.find(std::make_pair(non_terminal.get_name(),
                                                    follow_terminal.get_name()));
                if (it == table.end()) {
                    table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                            = *eps_prod;
                } else {
                    throw std::runtime_error(INVALID_LL1_GRAMMAR);
                }
            }
        }
        else
        {
            cfg_production synch_prod = *get_synch_prod();
            for (auto follow_terminal : follow)
            {
                auto it = table.find(make_pair(non_terminal.get_name(), follow_terminal.get_name()));
                if (it == table.end()) {
                    table[make_pair(non_terminal.get_name(), follow_terminal.get_name())]
                            = synch_prod;
                }
            }
        }
    }
}

cfg_production parsing_table::get_production (std::string rule, std::string token)
{
    return table[make_pair(rule, token)];
}

void parsing_table::draw(std::string file_name)
{
    // TODO :: write in file
    std::ofstream file;
    file.open(file_name);

    int max_size = 0;

    std::set<std::string> terminals_set;
    std::set<std::string> non_terminals_set;

    std::vector<std::string> terminals;
    std::vector<std::string> non_terminals;

    for (auto entry : table)
    {
        non_terminals_set.insert(entry.first.first);
        terminals_set.insert(entry.first.second);
        int length = entry.second.to_string().length();
        if (length > max_size) {
            max_size = length;
        }
    }

    for (auto const &s : terminals_set)
        terminals.push_back(s);

    for (auto const &s : non_terminals_set)
        non_terminals.push_back(s);


    file << '|' << std::setw(max_size) << "";
    for (auto const &t : terminals)
    {
        file << '|' << std::setw(max_size) << t ;
    }
    file << '|' << std::endl;


    for (int i = 0; i < max_size * (terminals.size() + 2); i++) file << "_";
    file << std::endl;

    for (int i = 0; i < non_terminals.size(); ++i)
    {
        file << '|' << std::setw(max_size) << non_terminals[i];
        for (int j = 0; j < terminals.size(); ++j)
        {
            if (get_production(non_terminals[i], terminals[j]).get_lhs_symbol().get_type() == SYNCH) {
                file << '|' << std::setw(max_size) << "SYNCH";
            } else {
                file << '|' << std::setw(max_size) << get_production(non_terminals[i], terminals[j]).to_string();
            }
        }
        file << '|' << std::endl;
        for (int i = 0; i < max_size * (terminals.size() + 2); i++) file << "_";
        file << std::endl;
    }

    file.close();
}


