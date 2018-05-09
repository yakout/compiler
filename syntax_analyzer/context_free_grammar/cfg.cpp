#include "cfg.h"
#include <fstream>
#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>


// *********************** UTILITIES *****************************

struct rule_holder {
    std::string lhs_symbol_name;
    std::vector <std::vector <std::string>> productions;
};

/**
 *  Splits a string according to a given character delimiter.
 */
void split_str (std::vector <std::string> &, std::string &, char);

/**
 *  Removes single quotes from string.
 */
bool remove_single_quotes (std::string &);

/**
 *  Trims leading and trailing spaces from string.
 */
void trim_spaces (std::string &);

rule_holder tokenize_rule (std::string &);

// ******************************************************************



cfg::cfg ()
        : non_terminals (), terminals () {

}

cfg::cfg (std::string grammar_file)
        : non_terminals (), terminals () {
    parse (grammar_file);
}

void cfg::parse (std::string & grammar_file) {
    std::ifstream grammar_in_file (grammar_file.c_str ());
    // Checks if grammar file exists or not.
    if (!grammar_in_file.good ()) {
        std::cout << grammar_file << ": File doesn't exist.\n";
        exit (EXIT_FAILURE);
    }
    std::string current_line, previous_line;
    bool first_line = true, first_rule = true;

    while (std::getline (grammar_in_file, current_line)) {
        if (first_line) {
            previous_line += current_line;
            first_line = false;
        } else {
            if (current_line[0] == '#') {
                // std::cout << previous_line << std::endl;
                parse_rule (previous_line, first_rule);
                if (first_rule)
                    first_rule = false;
                previous_line.clear ();
                previous_line += current_line;
            } else {
                previous_line += " " + current_line;
            }
        }
    }
    parse_rule (previous_line, first_rule);
    grammar_in_file.close ();
}

void cfg::parse_rule (std::string & rule_str, bool first_rule) {
    rule_holder r_h;
    r_h = tokenize_rule (rule_str);
    std::vector <cfg_production> productions;
    cfg_production prod;
    cfg_symbol lhs_symbol = cfg_symbol (r_h.lhs_symbol_name, cfg_symbol_type::NON_TERMINAL);
    non_terminals.insert (lhs_symbol);
    for (std::size_t i = 0 ; i < r_h.productions.size () ; i++) {
        cfg_production prod;
        prod.set_lhs_symbol (lhs_symbol);
        for (std::size_t j = 0 ; j < r_h.productions[i].size () ; j++) {
            cfg_symbol symbol;
            trim_spaces (r_h.productions[i][j]);
            if (r_h.productions[i][j] == "\\L" || remove_single_quotes (r_h.productions[i][j])) {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::TERMINAL);
                terminals.insert (symbol);
            } 
            else if (r_h.productions[i][j][0] == '@') {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::ACTION);
                std::function<void(std::vector<cfg_symbol>&)> func
                        = functions.find(r_h.productions[i][j].substr(1))->second;
                // TODO handle if the action doesn't exist
                 symbol.set_action(functions.find(r_h.productions[i][j].substr(1))->second);
            }
            else if (r_h.productions[i][j][0] == '#') {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::SYNTHESISED);
                // TODO handle if the record doesn't exist
                symbol.set_action(functions.find(r_h.productions[i][j].substr(1))->second);
            }
            else {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::NON_TERMINAL);
                non_terminals.insert (symbol);
            }
            prod.add_symbol (symbol);
        }
        // Builds the cfg_symbol_productions map.
        for (auto symbol : prod.get_symbols ())
            cfg_symbol_productions[symbol].push_back (prod);
        productions.push_back (prod);
    }
    if (first_rule)
        start_symbol = lhs_symbol;

    if (grammar.find (lhs_symbol) != grammar.end ())
        grammar[lhs_symbol].add_productions (productions);
    else
        add_rule (lhs_symbol, productions);
}

void cfg::add_rule (cfg_symbol & lhs_symbol
        , std::vector <cfg_production> & vec) {
    cfg_rule rule = cfg_rule (lhs_symbol, vec);
    grammar[lhs_symbol] = rule;
}

void cfg::add_rule (cfg_rule & rule) {
    grammar[rule.get_lhs_symbol ()] = rule;
}

void cfg::left_factor ()
{
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> new_grammar;

    for (auto grammar_entry : grammar)
    {
        std::map <std::string, std::vector <cfg_production>> common_factors;
        for (auto prod : grammar_entry.second.get_productions())
        {
            common_factors[prod.get_symbols()[0].get_name()].push_back (prod);
        }

        grammar_entry.second.empty_productions ();
        std::vector <cfg_production> new_productions;
        for (auto entry : common_factors)
        {
            if (entry.second.size() == 1)
            {
                new_productions.push_back (entry.second.front());
            }
            else
            {
                int common_prefix_size = longest_common_prefix(entry.second);
                std::vector<cfg_symbol> v;
                for (int i = 0; i < common_prefix_size; i++)
                {
                    v.push_back(entry.second.front().get_symbols()[i]);
                }

                std::string unique_new_symbol_name = grammar_entry.second.get_lhs_symbol().get_name() + "'";
                cfg_symbol temp(unique_new_symbol_name, TERMINAL);
                while (new_grammar.find(temp) != new_grammar.end() || grammar.find(temp) != grammar.end()) {
                    unique_new_symbol_name += "'";
                    temp = cfg_symbol(unique_new_symbol_name, TERMINAL);
                }

                cfg_symbol new_sym(unique_new_symbol_name, grammar_entry.second.get_lhs_symbol().get_type());

                v.push_back(new_sym);
                cfg_symbol original_symbol(cfg_symbol(grammar_entry.second.get_lhs_symbol()));
                cfg_production new_prod(original_symbol, v);
                new_productions.push_back (new_prod);

                // construct the new rules
                std::vector<cfg_production> productions_vec;

                for (auto prod : entry.second)
                {
                    std::vector<cfg_symbol> rest_symbols;
                    for (int i = common_prefix_size; i < prod.get_symbols().size(); i++)
                    {
                        rest_symbols.push_back(prod.get_symbols()[i]);
                    }
                    if (rest_symbols.empty()) {
                        cfg_symbol eps("\\L", TERMINAL);
                        rest_symbols.push_back(eps);
                    }
                    cfg_production rest_symbols_as_production(new_sym, rest_symbols);
                    productions_vec.push_back(rest_symbols_as_production);
                }
                cfg_rule new_rule(new_sym, productions_vec);
                non_terminals.insert(new_sym);

                cfg temp_cfg;
                std::unordered_map <cfg_symbol, cfg_rule
                        , cfg_symbol::hasher, cfg_symbol::comparator> temp_grammar;

                temp_grammar[new_sym] = new_rule;
                temp_cfg.set_grammar(temp_grammar);
                temp_cfg.left_factor();

                for (auto temp_cfg_entry : temp_cfg.get_grammar())
                {
                    new_grammar[temp_cfg_entry.first] = temp_cfg_entry.second;
                }
            }
        }
        cfg_symbol sym(grammar_entry.first);
        cfg_rule new_rule(sym, new_productions);
        new_grammar[sym] = new_rule;
    }
    grammar = new_grammar;
}

void cfg::remove_left_recursion ()
{
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> new_grammar;
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> cfg_symbol_prods;

    for (int i = 0; i < get_rules().size(); i++) {
        cfg_rule old_rule = get_rules()[i];
        cfg_rule rule = old_rule;

        // try to substitue
        for (int j = 0; j <= i - 1; j++)
        {
            rule = substitue(new_grammar[get_rules()[j].get_lhs_symbol()], old_rule);
        }

        std::vector<cfg_production> target_prods;
        std::vector<cfg_production> rest_prods;
        bool is_left_recursion = false;

        for (auto prod : rule.get_productions()) {
            if (prod.get_symbols().front() == rule.get_lhs_symbol()) {
                is_left_recursion = true;
                target_prods.push_back(prod);
            } else {
                rest_prods.push_back(prod);
            }
        }

        if (!is_left_recursion) {
            for (auto prod : rule.get_productions()) {
                for (auto sym : prod.get_symbols()) {
                    cfg_symbol_prods[sym].push_back(prod);
                }
            }
            new_grammar[rule.get_lhs_symbol()] = rule;
            continue;
        }

        // Modifying old rule
        std::string unique_new_symbol_name = rule.get_lhs_symbol().get_name() + "'";
        cfg_symbol temp(unique_new_symbol_name, TERMINAL);

        while (new_grammar.find(temp) != new_grammar.end() || grammar.find(temp) != grammar.end()) {
            unique_new_symbol_name += "'";
            temp = cfg_symbol(unique_new_symbol_name, TERMINAL);
        }

        cfg_symbol new_symbol(unique_new_symbol_name, NON_TERMINAL);
        rule.empty_productions();

        for (auto it = rest_prods.begin(); it != rest_prods.end(); it++)
        {
            if ((*it).get_symbols().front().get_name() == EPS)
            {
                // if it's eps production remove it and add the new symbol
                (*it).pop_first_symbol();
                (*it).add_symbol(new_symbol);
            } else {
                // if it's not eps production append the new_symbol
                (*it).add_symbol(new_symbol);
            }
            for (auto sym : (*it).get_symbols()) {
                cfg_symbol_prods[sym].push_back((*it));
            }
        }
        rule.set_productions(rest_prods);
        new_grammar[rule.get_lhs_symbol()] = rule;

        // Constructing new rule
        cfg_symbol eps("\\L", TERMINAL);
        std::vector<cfg_symbol> v;
        v.push_back(eps);
        cfg_production eps_prod(new_symbol, v);

        for (auto it = target_prods.begin(); it != target_prods.end(); it++)
        {
            (*it).pop_first_symbol();
            (*it).add_symbol(new_symbol);
            (*it).set_lhs_symbol(new_symbol);
            for (auto sym : (*it).get_symbols()) {
                cfg_symbol_prods[sym].push_back((*it));
            }
        }

        target_prods.push_back(eps_prod);

        cfg::non_terminals.insert(new_symbol);
        cfg_rule new_rule(new_symbol, target_prods);
        new_grammar[new_symbol] = new_rule;
    }

    cfg::cfg_symbol_productions = cfg_symbol_prods;
    cfg::grammar = new_grammar;
}

std::unordered_set <cfg_symbol, cfg_symbol::hasher
        , cfg_symbol::comparator> cfg::get_non_terminals () {
    return non_terminals;
}

std::unordered_set <cfg_symbol, cfg_symbol::hasher
        , cfg_symbol::comparator> cfg::get_terminals () {
    return terminals;
}

cfg_symbol cfg::get_start_symbol () {
    return start_symbol;
}

std::vector <cfg_rule> cfg::get_rules () {
    std::vector <cfg_rule> rules;
    for (auto entry : grammar) {
        rules.push_back (entry.second);
    }
    return rules;
}

void
cfg::process_first_set(int prod_symbol_index, std::shared_ptr<first_set> first_set,
                       cfg_production *prod) {
    if (prod_symbol_index == prod->get_symbols().size()) {
        return;
    }
    auto curr_prod_symbol = prod->get_symbols()[prod_symbol_index];

    if (!curr_prod_symbol.is_term_or_non_term()) {
        process_first_set(prod_symbol_index + 1, first_set, prod);
    }
    // Cycle case
    if (curr_prod_symbol.get_name() == prod->get_lhs_symbol().get_name()) {
        return;
    }

    if (curr_prod_symbol.get_type() == TERMINAL) {
        first_set->add_symbol(curr_prod_symbol.get_name(), curr_prod_symbol, nullptr);
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), curr_prod_symbol, prod);
        return;
    }

    // If current prod symbol isn't processed yet, process it.
    if (first_set->empty(curr_prod_symbol.get_name())) {
        // Go to curr_prod_symbol rule and iterate over all its prods and calc its first set.
        for (auto it = cfg::grammar[curr_prod_symbol].get_productions().begin();
             it != cfg::grammar[curr_prod_symbol].get_productions().end(); it++)
        {
            process_first_set(0, first_set, &(*it));
        }
    }

    // Here curr_proc_symbol's first_set should be already processed.
    auto symbols_map = first_set->get_set_map();
    for (auto symbol : symbols_map[curr_prod_symbol.get_name()]) {
        // Add all symbols of curr_prod_symbol to lhs symbol's first set
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), symbol.first, prod);
    }

    // If curr_prod_symbol has eps in its first set, then continue processing this production.
    if (first_set->has_eps(curr_prod_symbol.get_name())) {
        cfg_symbol eps(EPS, TERMINAL); // TODO: Make this a constant.
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), eps, prod);
        process_first_set(prod_symbol_index + 1, first_set, prod);
    }
}

std::shared_ptr<first_set> cfg::get_first_set() {
    std::shared_ptr<first_set> first_set_ptr = std::make_shared<first_set>();

    /// Build first set
    for (auto non_terminal : cfg::non_terminals) {
        //std::cout << "Current non_terminal = " << non_terminal.to_string() << "\n";
        if (!first_set_ptr->empty(non_terminal.get_name())) {
            continue;
        }
        auto rule = cfg::grammar[non_terminal];
        //std::cout << "Current rule has lhs = " << rule.get_lhs_symbol().to_string() << "\n";

        for (auto it = cfg::grammar[non_terminal].get_productions().begin();
             it != cfg::grammar[non_terminal].get_productions().end(); it++)
        {
            process_first_set(0, first_set_ptr, &(*it));
        }
    }
    for (auto terminal : cfg::terminals) {
        auto set_map = first_set_ptr->get_set_map();
        if (set_map[terminal.get_name()].empty()) {
            first_set_ptr->add_symbol(terminal.get_name(), terminal, nullptr);
        }
    }
    return first_set_ptr;
}

bool cfg::is_last_symbol(int pos, cfg_production production) {
    pos++;
    while (pos != production.get_symbols().size()) {
        if (!production.get_symbols()[pos].is_term_or_non_term()) {
            pos++;
            continue;
        }
        return false;
    }
    return true;
}

int cfg::get_next_sym_pos(int pos, cfg_production production) {
    if (pos + 1 == production.get_symbols().size())
        return pos;
    pos++;
    while (pos < production.get_symbols().size() && !production.get_symbols()[pos].is_term_or_non_term()) {
        pos++;
    }
    return pos;
}

void cfg::process_follow_set(cfg_symbol non_terminal, std::shared_ptr<follow_set> follow_set_ptr) {
    if (non_terminal.get_name() == cfg::start_symbol.get_name()) {
        cfg_symbol s_$("$", END_MARKER);
        follow_set_ptr->add_symbol(non_terminal.get_name(), s_$);
    }
    for (auto production : cfg::cfg_symbol_productions[non_terminal]) {
        for (int i = 0; i < production.get_symbols().size(); i++) {
            auto symbol = production.get_symbols()[i];
            if (!symbol.is_term_or_non_term())
                continue;
            if (symbol.get_name() == non_terminal.get_name()) {
                bool last_sym = is_last_symbol(i, production);
                if (last_sym) {
                    // This non_terminal is the last symbol in the production.
                    if (follow_set_ptr->empty(production.get_lhs_symbol().get_name())
                        && production.get_lhs_symbol().get_name() != non_terminal.get_name()) {
                        // Calc Follow(lhs) if not calculated
                        process_follow_set(production.get_lhs_symbol(), follow_set_ptr);
                    }
                    // Add everything in Follow(lhs) to Follow(non_terminal)
                    /// TODO: Make this a function in the cfg_set class.
                    auto follow_set_map = follow_set_ptr->get_set_map();

                    for (auto symbol : follow_set_map[production.get_lhs_symbol().get_name()]) {
                        follow_set_ptr->add_symbol(non_terminal.get_name(), symbol);
                    }
                } else {
                    // There is a symbol after this non_terminal in the production.

                    bool has_eps = true;
                    int curr_pos = get_next_sym_pos(i, production);
                    while (has_eps) {
                        has_eps = false;
                        // Put everything in first of the next symbol in the follow of non_terminal
                        auto cfg_first_set_map = cfg::get_first_set()->get_set_map();
                        auto next_first_set = cfg_first_set_map[production.get_symbols()[curr_pos].get_name()];
                        for (auto symbol : next_first_set) {
                            if (symbol.first.get_name() != EPS) {
                                follow_set_ptr->add_symbol(non_terminal.get_name(), symbol.first);
                            } else {
                                has_eps = true;
                            }
                        }
                        curr_pos = get_next_sym_pos(curr_pos, production);
                        if (is_last_symbol(curr_pos, production)) {
                            break;
                        }
                    }
                    if (has_eps) {
                        // If eps is in first of last symbol, add everything in Follow(lhs) to Follow(non_terminal)
                        if (follow_set_ptr->empty(production.get_lhs_symbol().get_name())) {
                            // Calc Follow(lhs) if not calculated
                            process_follow_set(production.get_lhs_symbol(), follow_set_ptr);
                        }
                        // Add everything in Follow(lhs) to Follow(non_terminal)
                        // TODO: Make this a function in first_set
                        auto follow_set_map = follow_set_ptr->get_set_map();
                        for (auto symbol : follow_set_map[production.get_lhs_symbol().get_name()]) {
                            follow_set_ptr->add_symbol(non_terminal.get_name(), symbol);
                        }
                    }
                }
//                break;
            }
        }
    }
}

std::shared_ptr<follow_set> cfg::get_follow_set() {
    std::shared_ptr<follow_set> follow_set_ptr = std::make_shared<follow_set>();
    for (auto non_terminal : cfg::non_terminals) {
        if (!follow_set_ptr->empty(non_terminal.get_name())) {
            continue;
        }
        process_follow_set(non_terminal, follow_set_ptr);
    }
    return follow_set_ptr;
}

void cfg::set_non_terminals(const std::unordered_set<cfg_symbol
        , cfg_symbol::hasher, cfg_symbol::comparator> & non_terminals) {
    cfg::non_terminals = non_terminals;
}

const std::unordered_map<cfg_symbol, cfg_rule, cfg_symbol::hasher
        , cfg_symbol::comparator> &cfg::get_grammar() const {
    return grammar;
}

void
cfg::set_grammar(const std::unordered_map<cfg_symbol, cfg_rule
        , cfg_symbol::hasher, cfg_symbol::comparator> &grammar) {
    cfg::grammar = grammar;
}

void cfg::set_start_symbol(const cfg_symbol &start_symbol) {
    cfg::start_symbol = start_symbol;
}

const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &
cfg::get_cfg_symbol_productions() const {
    return cfg_symbol_productions;
}

void cfg::set_cfg_symbol_productions(
        const std::unordered_map<cfg_symbol, std::vector<cfg_production>, cfg_symbol::hasher, cfg_symbol::comparator> &cfg_symbol_productions) {
    cfg::cfg_symbol_productions = cfg_symbol_productions;
}

void cfg::set_terminals(const std::unordered_set <cfg_symbol, cfg_symbol::hasher
        , cfg_symbol::comparator> &terminals) {
    cfg::terminals = terminals;
}

void cfg::print_cfg_symbol_productions_map() {
    std::cout << "============================PRINTING CFG SYMBOLS PRODUCTIONS MAP==================================\n";
    for (auto non_term : cfg::non_terminals) {
        std::cout << "PRODUCTIONS(" << non_term.get_name() << ") = {";
        auto temp_map = cfg::cfg_symbol_productions;
        for (auto prod : temp_map[non_term]){
            std::cout << prod.to_string() << "  ";
        }
        std::cout << "}\n";
    }
    std::cout << "==================================================================================================\n";
}

void cfg::add_function(std::string name, std::function<void(std::vector<cfg_symbol> &)> func)
{
    functions.insert({name, func});
}

void split_str (std::vector <std::string> & vec
        , std::string & str, char delimiter) {
    std::stringstream ss_str (str);
    std::string token;
    while (getline (ss_str, token, delimiter))
        vec.push_back (token);
    return;
}

bool remove_single_quotes (std::string & str) {
    if (str[0] == '\'' && str[str.length () - 1] == '\'') {
        str.erase (remove ( str.begin(), str.end(), '\'' ), str.end ());
        return true;
    }
    return false;
}

rule_holder tokenize_rule (std::string & str) {
    rule_holder r_h;
    std::vector <std::string> vec;
    str.erase (0, 1);
    // Gets the position of the first equal sign to split the rule to LHS and RHS.
    std::size_t equal_sign_pos = str.find_first_of ("=");
    if (equal_sign_pos == std::string::npos) {
        //TODO: Report "Invalid rule so invalid grammar" error.
    }

    std::string lhs_symbol_name = str.substr (0, equal_sign_pos - 1);
    trim_spaces (lhs_symbol_name);

    std::string rhs_productions = str.substr (equal_sign_pos + 1, str.length ());
    trim_spaces (rhs_productions);

    r_h.lhs_symbol_name = lhs_symbol_name;
    split_str (vec, rhs_productions, '|');
    for (std::size_t i = 0 ; i < vec.size (); i++) {
        std::vector <std::string> prod;
        trim_spaces (vec[i]);
        split_str (prod, vec[i], ' ');
        r_h.productions.push_back (prod);
        prod.clear ();
    }
    return r_h;
}

void trim_spaces (std::string & str) {
    // trim leading spaces.
    str.erase (str.begin (), std::find_if (str.begin (), str.end (), [](int character) {
        return !std::isspace (character);
    }));

    // trim trailing spaces.
    str.erase (std::find_if (str.rbegin (), str.rend (), [](int character) {
        return !std::isspace (character);
    }).base (), str.end ());
}


int longest_common_prefix(std::vector<cfg_production> prods)
{
    cfg_production prod = prods.front();

    int i;
    for (i = 0; i < prod.get_symbols().size(); i++) {
        for (int j = 1; j < prods.size(); j++) {
            if (prods[j].get_symbols().size() >= i) {
                if (prods[j].get_symbols()[i] == prod.get_symbols()[i]) {
                    continue;
                } else {
                    return i;
                }
            } else {
                return i;
            }
        }
    }
    return i;
}

cfg_rule substitue(cfg_rule rule1, cfg_rule rule2)
{
    // goal: sub rule1 in rule2
    cfg_symbol rule1_symbol = rule1.get_lhs_symbol();
    std::vector<cfg_production> new_productions;

    for (auto prod : rule2.get_productions()) 
    {
        int symbol_index = prod.find(rule1_symbol);

        if (symbol_index != -1) {
            if (symbol_index != 0) {
                // if it's not in the left of production then it's not potential for left recursion
                // and no need to substitue.
                new_productions.push_back(prod);
                continue;
            }

            std::vector<cfg_symbol> old_rhs_symbols;

            for (int i = symbol_index + 1; i < prod.get_symbols().size(); i++)
            {
                old_rhs_symbols.push_back(prod.get_symbols()[i]);
            }

            // make the new productions
            for (auto rule1_prod : rule1.get_productions())
            {
                std::vector<cfg_symbol> new_symbols;

                for (auto symbol : rule1_prod.get_symbols())
                {
                    if (symbol.get_name() != EPS)
                    new_symbols.push_back(symbol);
                }

                for (auto symbol : old_rhs_symbols)
                {
                    new_symbols.push_back(symbol);
                }

                cfg_symbol temp_symbol(prod.get_lhs_symbol());
                cfg_production new_prod(temp_symbol, new_symbols);
                new_productions.push_back(new_prod);
            }

        } else {
            new_productions.push_back(prod);
        }
    }

    cfg_symbol temp_symbol(rule2.get_lhs_symbol());
    cfg_rule new_rule(temp_symbol, new_productions);

    return new_rule;
}
