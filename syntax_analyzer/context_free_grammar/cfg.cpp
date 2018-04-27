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
 *  TODO: Re-check this.
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
        //TODO: Report "File doesn't exist!" error.
    }
    std::string current_line, previous_line;
    bool first_line = true, first_rule = true;

    while (std::getline (grammar_in_file, current_line)) {
        if (first_line) {
            previous_line += current_line;
            first_line = false;
        } else {
            if (current_line[0] == '#') {
                std::cout << "READ A WHOLE RULE." << std::endl;     // DEBUGGING
                std::cout << previous_line << std::endl;
                parse_rule (previous_line, first_rule);
                std::cout << "PARSED A WHOLE RULE." << std::endl;
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
}

void cfg::parse_rule (std::string & rule_str, bool first_rule) {
    rule_holder r_h;
    std::cout << "ENTERED parse_rule () FUNCTION." << std::endl;
    r_h = tokenize_rule (rule_str);
    std::cout << "parse_rule (): PASSED TOKENIZING RULE TO TWO PARTS." << std::endl;
    std::vector <cfg_production> productions;
    cfg_production prod;
    cfg_symbol lhs_symbol = cfg_symbol (r_h.lhs_symbol_name, cfg_symbol_type::NON_TERMINAL);
    std::cout << "parse_rule (): CREATED LHS SYMBOL OF RULE." << std::endl;
    for (std::size_t i = 0 ; i < r_h.productions.size () ; i++) {
        std::cout << "parse_rule (): BUILDING PRODUCTION # " << i << std::endl;
        cfg_production prod;
        prod.set_lhs_symbol (lhs_symbol);
        for (std::size_t j = 0 ; j < r_h.productions[i].size () ; j++) {
            std::cout << "parse_rule (): BUILDING PRODUCTION # " << i
                << " SYMBOL # " << j << std::endl;
            cfg_symbol symbol;
            trim_spaces (r_h.productions[i][j]);
            if (r_h.productions[i][j] == "\\L" || remove_single_quotes (r_h.productions[i][j])) {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::TERMINAL);
                terminals.insert (symbol);
            } else {
                symbol = cfg_symbol (r_h.productions[i][j], cfg_symbol_type::NON_TERMINAL);
                non_terminals.insert (symbol);
            }
            prod.add_symbol (symbol);
        }
        // Builds the cfg_symbol_productions map.
        for (auto symbol : prod.get_symbols ())
            cfg_symbol_productions[symbol].push_back (prod);
        std::cout << "parse_rule (): BUILT THE cfg_symbol_productions MAP." << std::endl;
        productions.push_back (prod);
        std::cout << "parse_rule (): ADDED PRODUCTION TO THE PRODUCTIONS VECTOR." << std::endl;
    }
    if (first_rule)
        start_symbol = lhs_symbol;
    
    if (grammar.find (lhs_symbol) != grammar.end ())
        grammar[lhs_symbol].add_productions (productions);
    else 
        add_rule (lhs_symbol, productions);
    std::cout << "parse_rule (): ADDED RULE TO GRAMMAR AND RULES VECTOR." << std::endl;
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
     for (auto grammar_entry : grammar)
     {
         std::map <std::vector<std::string>, std::vector <cfg_production>> common_factors;
         for (auto prod : grammar_entry.second.get_productions())
         {
             std::vector<std::string> v;
             // find longest common prefix
             v.push_back(prod.get_symbols()[0].get_name());
             common_factors[v].push_back (prod);
         }

         grammar_entry.second.empty_productions ();
         size_t counter = 1;
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

                 cfg_symbol new_sym(grammar_entry.second.get_lhs_symbol().get_name()
                     + std::to_string(counter), grammar_entry.second.get_lhs_symbol().get_type());
                 counter++;

                 v.push_back(new_sym);
                 cfg_symbol original_symbol(cfg_symbol(grammar_entry.second.get_lhs_symbol()));
                 cfg_production new_prod(original_symbol, v);
                 new_productions.push_back (new_prod);

                 for (auto prod : entry.second)
                 {
                     std::vector<cfg_symbol> rest_symbols;
                     for (int i = common_prefix_size; i < prod.get_symbols().size(); i++)
                     {
                         rest_symbols.push_back(prod.get_symbols()[i]);
                     }
                     cfg_production rest_symbols_as_production(new_sym, rest_symbols);
                     std::vector<cfg_production> productions_vec;
                     productions_vec.push_back(rest_symbols_as_production);
                     add_rule(new_sym, productions_vec);
                 }
             }
         }
     }
}

void cfg::remove_left_recursion ()
{

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

bool cfg::is_ll_1 () {
    return true;
}

void
cfg::process_first_set(int prod_symbol_index, std::shared_ptr<first_set> first_set,
                       cfg_production *prod) {
    if (prod_symbol_index == prod->get_symbols().size()) {
        return;
    }
    auto curr_prod_symbol = prod->get_symbols()[prod_symbol_index];

    // Cycle case
    if (curr_prod_symbol.get_name() == prod->get_lhs_symbol().get_name()) {
        return;
    }

    if (curr_prod_symbol.get_type() == TERMINAL) {
        first_set->add_symbol(curr_prod_symbol.get_name(), curr_prod_symbol, prod);
        first_set->add_symbol(prod->get_lhs_symbol().get_name(), curr_prod_symbol, prod);
        return;
    }

    // If current prod symbol isn't processed yet, process it.
    if (first_set->empty(curr_prod_symbol.get_name())) {
        // Go to curr_prod_symbol rule and iterate over all its prods and calc its first set.
        for (auto production : cfg::grammar[curr_prod_symbol].get_productions()) {
            process_first_set(0, first_set, &production);
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
        for (auto production : cfg::grammar[non_terminal].get_productions()) { // Iterate over all productions from this non-terminal
            //std::cout << "Current production's lhs = " << production.get_lhs_symbol().to_string() << "\n";
            process_first_set(0, first_set_ptr, &production);
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

void cfg::process_follow_set(cfg_symbol non_terminal, std::shared_ptr<follow_set> follow_set_ptr) {
    if (non_terminal.get_name() == cfg::start_symbol.get_name()) {
        cfg_symbol s_$("$", END_MARKER);
        follow_set_ptr->add_symbol(non_terminal.get_name(), s_$);
    }
    for (auto production : cfg::cfg_symbol_productions[non_terminal]) {
        for (int i = 0; i < production.get_symbols().size(); i++) {
            auto symbol = production.get_symbols()[i];
            if (symbol.get_name() == non_terminal.get_name()) {
                if (i + 1 == production.get_symbols().size()) {
                    // This non_terminal is the last symbol in the production.
                    if (follow_set_ptr->empty(production.get_lhs_symbol().get_name())) {
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
                    int curr_pos = i + 1;
                    while (has_eps) {
                        if (curr_pos == production.get_symbols().size()) {
                            break;
                        }
                        has_eps = false;
                        // Put everything in first of the next symbol in the follow of non_terminal
                        auto cfg_first_set_map = cfg::get_first_set()->get_set_map();
//                        for (auto elem : cfg_first_set_map) {
//                            std::cout << elem.first << "\n";
//                        }
                        auto next_first_set = cfg_first_set_map[production.get_symbols()[curr_pos++].get_name()];
                        for (auto symbol : next_first_set) {
                            if (symbol.first.get_name() != EPS) {
                                follow_set_ptr->add_symbol(non_terminal.get_name(), symbol.first);
                            } else {
                                has_eps = true;
                            }
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
                break;
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
//        std::cout << "Calculating follow of non_terminal = " << non_terminal.to_string() << "\n";
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
    std::cout << "ENTERED tokenize_rule () FUNCTION." << std::endl;
    str.erase (0, 1);
    std::cout << "tokenize_rule (): ERASED FIRST HASH CHARACTER: " << str << std::endl;
    // Gets the position of the first equal sign to split the rule to LHS and RHS.
    std::size_t equal_sign_pos = str.find_first_of ("=");
    std::cout << "tokenize_rule (): FOUND THE POSITION OF THE EQUAL SIGN = " << equal_sign_pos << std::endl;
    if (equal_sign_pos == std::string::npos) {
        //TODO: Report "Invalid rule so invalid grammar" error.
    }

    std::string lhs_symbol_name = str.substr (0, equal_sign_pos - 1);
    trim_spaces (lhs_symbol_name);
    std::cout << "tokenize_rule (): PARSED THE LHS SYMBOL NAME >>> " << lhs_symbol_name
            << " LENGTH >>> " << lhs_symbol_name.length () << std::endl;

    std::string rhs_productions = str.substr (equal_sign_pos + 1, str.length ());
    trim_spaces (rhs_productions);
    std::cout << "tokenize_rule (): PARSED THE RHS PRODUCTIONS >>> " << rhs_productions
            << " LENGTH >>> " << rhs_productions.length () << std::endl;


    r_h.lhs_symbol_name = lhs_symbol_name;
    std::cout << "tokenize_rule (): SET THE LHS SYMBOL NAME IN THE RHS HOLDER." << std::endl;
    split_str (vec, rhs_productions, '|');
    std::cout << "tokenize_rule (): SPLITTED THE RHS PRODUCTIONS TO SINGLE PRODUCTIONS." << std::endl;
    for (std::size_t i = 0 ; i < vec.size (); i++) {
        std::vector <std::string> prod;
        trim_spaces (vec[i]);
        std::cout << "tokenize_rule (): TRIMMED PRODUCTION >>> " << i << " STRING >>> " << vec[i] << std::endl;
        split_str (prod, vec[i], ' ');
        std::cout << "tokenize_rule (): SPLITTED PRODUCTION >>> " << i << " STRING TO SYMBOLS >>> " << vec[i] << std::endl;
        r_h.productions.push_back (prod);
        std::cout << "tokenize_rule (): ADDED PRODUCTION >>> " << i << " TO PRODUCTION RULE." << std::endl;
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