#include "../../lib/catch.hpp"
#include "../../../syntax_analyzer/predictive_parser.h"
#include <memory>


TEST_CASE("TEST FIRST_SIMPLE")
{
    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod_vector;
    std::vector<cfg_symbol> E_dash_prod_vector;

    std::vector<cfg_symbol> T_prod_vector;
    std::vector<cfg_symbol> T_dash_prod_vector;

    std::vector<cfg_symbol> F_prod_vector1;
    std::vector<cfg_symbol> F_prod_vector2;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$(END_MARKER);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol E("E", NON_TERMINAL);
    cfg_symbol E_dash("E'", NON_TERMINAL);
    cfg_symbol T("T", NON_TERMINAL);
    cfg_symbol T_dash("T'", NON_TERMINAL);
    cfg_symbol F("F", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol multiplication("*", TERMINAL);
    cfg_symbol left_paren("(", TERMINAL);
    cfg_symbol right_paren(")", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    // E -> TE'
    E_prod_vector.push_back(T);
    E_prod_vector.push_back(E_dash);

    // E' -> +TE'
    E_dash_prod_vector.push_back(plus);
    E_dash_prod_vector.push_back(T);
    E_dash_prod_vector.push_back(E_dash);

    // T -> FT'
    T_prod_vector.push_back(F);
    T_prod_vector.push_back(T_dash);

    // T' -> *FT'
    T_dash_prod_vector.push_back(multiplication);
    T_dash_prod_vector.push_back(F);
    T_dash_prod_vector.push_back(T_dash);

    // F -> (E)
    F_prod_vector1.push_back(left_paren);
    F_prod_vector1.push_back(E);
    F_prod_vector1.push_back(right_paren);

    // F -> id
    F_prod_vector2.push_back(id);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_E(E, E_prod_vector);
    cfg_production prod_E_dash(E_dash, E_dash_prod_vector);
    cfg_production prod_E_dash_eps(E_dash, eps_vector);

    cfg_production prod_T(T, T_prod_vector);
    cfg_production prod_T_dash(T_dash, T_dash_prod_vector);
    cfg_production prod_T_dash_eps(T_dash, eps_vector);

    cfg_production prod_F1(F, F_prod_vector1);
    cfg_production prod_F2(F, F_prod_vector2);

    std::map<std::pair<std::string, std::string>, cfg_production> table;
    std::shared_ptr<cfg> cfg_ptr = std::make_shared<cfg>(cfg ());

    // Building non_terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> non_terminals;
    non_terminals.insert(E);
    non_terminals.insert(E_dash);
    non_terminals.insert(T_dash);
    non_terminals.insert(T);
    non_terminals.insert(F);
    cfg_ptr->set_non_terminals(non_terminals);

    // Building terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> terminals;
    terminals.insert(eps);
    terminals.insert(plus);
    terminals.insert(multiplication);
    terminals.insert(left_paren);
    terminals.insert(right_paren);
    terminals.insert(id);
    cfg_ptr->set_terminals(terminals);

    // Building grammar
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    std::vector<cfg_production> E_productions;
    std::vector<cfg_production> T_productions;
    std::vector<cfg_production> F_productions;
    std::vector<cfg_production> E_dash_productions;
    std::vector<cfg_production> T_dash_productions;
    E_productions.push_back(prod_E);
    E_dash_productions.push_back(prod_E_dash);
    E_dash_productions.push_back(prod_E_dash_eps);
    T_productions.push_back(prod_T);
    T_dash_productions.push_back(prod_T_dash);
    T_dash_productions.push_back(prod_T_dash_eps);
    F_productions.push_back(prod_F1);
    F_productions.push_back(prod_F2);

    // Building rules
    cfg_rule rule_E(E, E_productions);
    cfg_rule rule_E_dash(E_dash, E_dash_productions);
    cfg_rule rule_T_dash(T_dash, T_dash_productions);
    cfg_rule rule_T(T, T_productions);
    cfg_rule rule_F(F, F_productions);

    grammar[E] = rule_E;
    grammar[T] = rule_T;
    grammar[E_dash] = rule_E_dash;
    grammar[T_dash] = rule_T_dash;
    grammar[F] = rule_F;
    cfg_ptr->set_grammar(grammar);
    cfg_ptr->set_start_symbol(E);

    // Building map of symbols and their corresponding productions.
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> sym_productions;
    sym_productions[E].push_back(prod_F1);
    sym_productions[E_dash].push_back(prod_E);
    sym_productions[E_dash].push_back(prod_E_dash);
    sym_productions[T].push_back(prod_E);
    sym_productions[T].push_back(prod_E_dash);
    sym_productions[T_dash].push_back(prod_T);
    sym_productions[T_dash].push_back(prod_T_dash);
    sym_productions[F].push_back(prod_T);
    sym_productions[F].push_back(prod_T_dash);
    cfg_ptr->set_cfg_symbol_productions(sym_productions);

    // Validating first of terminals.
    auto first_set_map = cfg_ptr->get_first_set()->get_set_map();
    for (auto symbol : terminals) {
        auto curr_set = first_set_map[symbol.get_name()];
        REQUIRE(curr_set.size() == 1);
        for (auto sym : curr_set) {
            REQUIRE(symbol.get_name() == sym.first.get_name());
        }
    }

    // Validating first of non_terminals.
    std::map<std::string, std::set<std::string>> reference_sets;
    reference_sets["E"].insert("id");
    reference_sets["E"].insert("(");
    reference_sets["T"].insert("(");
    reference_sets["T"].insert("id");
    reference_sets["E'"].insert("\\L");
    reference_sets["E'"].insert("+");
    reference_sets["F"].insert("id");
    reference_sets["F"].insert("(");
    reference_sets["T'"].insert("\\L");
    reference_sets["T'"].insert("*");
    for (auto symbol : non_terminals) {
        auto curr_first_set = first_set_map[symbol.get_name()];
        std::set<std::string> curr_set;
        for (auto sym : curr_first_set) {
            curr_set.insert(sym.first.get_name());
        }
        REQUIRE(curr_set == reference_sets[symbol.get_name()]);
    }
}

TEST_CASE("TEST FOLLOW_SIMPLE")
{
    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod_vector;
    std::vector<cfg_symbol> E_dash_prod_vector;

    std::vector<cfg_symbol> T_prod_vector;
    std::vector<cfg_symbol> T_dash_prod_vector;

    std::vector<cfg_symbol> F_prod_vector1;
    std::vector<cfg_symbol> F_prod_vector2;

    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$(END_MARKER);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol E("E", NON_TERMINAL);
    cfg_symbol E_dash("E'", NON_TERMINAL);
    cfg_symbol T("T", NON_TERMINAL);
    cfg_symbol T_dash("T'", NON_TERMINAL);
    cfg_symbol F("F", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol plus("+", TERMINAL);
    cfg_symbol multiplication("*", TERMINAL);
    cfg_symbol left_paren("(", TERMINAL);
    cfg_symbol right_paren(")", TERMINAL);
    cfg_symbol id("id", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    eps_vector.push_back(eps);

    // E -> TE'
    E_prod_vector.push_back(T);
    E_prod_vector.push_back(E_dash);

    // E' -> +TE'
    E_dash_prod_vector.push_back(plus);
    E_dash_prod_vector.push_back(T);
    E_dash_prod_vector.push_back(E_dash);

    // T -> FT'
    T_prod_vector.push_back(F);
    T_prod_vector.push_back(T_dash);

    // T' -> *FT'
    T_dash_prod_vector.push_back(multiplication);
    T_dash_prod_vector.push_back(F);
    T_dash_prod_vector.push_back(T_dash);

    // F -> (E)
    F_prod_vector1.push_back(left_paren);
    F_prod_vector1.push_back(E);
    F_prod_vector1.push_back(right_paren);

    // F -> id
    F_prod_vector2.push_back(id);
    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_E(E, E_prod_vector);
    cfg_production prod_E_dash(E_dash, E_dash_prod_vector);
    cfg_production prod_E_dash_eps(E_dash, eps_vector);

    cfg_production prod_T(T, T_prod_vector);
    cfg_production prod_T_dash(T_dash, T_dash_prod_vector);
    cfg_production prod_T_dash_eps(T_dash, eps_vector);

    cfg_production prod_F1(F, F_prod_vector1);
    cfg_production prod_F2(F, F_prod_vector2);

    std::map<std::pair<std::string, std::string>, cfg_production> table;
    std::shared_ptr<cfg> cfg_ptr = std::make_shared<cfg>(cfg ());

    // Building non_terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> non_terminals;
    non_terminals.insert(E);
    non_terminals.insert(E_dash);
    non_terminals.insert(T_dash);
    non_terminals.insert(T);
    non_terminals.insert(F);
    cfg_ptr->set_non_terminals(non_terminals);

    // Building terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> terminals;
    terminals.insert(eps);
    terminals.insert(plus);
    terminals.insert(multiplication);
    terminals.insert(left_paren);
    terminals.insert(right_paren);
    terminals.insert(id);
    cfg_ptr->set_terminals(terminals);

    // Building grammar
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    std::vector<cfg_production> E_productions;
    std::vector<cfg_production> T_productions;
    std::vector<cfg_production> F_productions;
    std::vector<cfg_production> E_dash_productions;
    std::vector<cfg_production> T_dash_productions;
    E_productions.push_back(prod_E);
    E_dash_productions.push_back(prod_E_dash);
    E_dash_productions.push_back(prod_E_dash_eps);
    T_productions.push_back(prod_T);
    T_dash_productions.push_back(prod_T_dash);
    T_dash_productions.push_back(prod_T_dash_eps);
    F_productions.push_back(prod_F1);
    F_productions.push_back(prod_F2);

    // Building rules
    cfg_rule rule_E(E, E_productions);
    cfg_rule rule_E_dash(E_dash, E_dash_productions);
    cfg_rule rule_T_dash(T_dash, T_dash_productions);
    cfg_rule rule_T(T, T_productions);
    cfg_rule rule_F(F, F_productions);

    grammar[E] = rule_E;
    grammar[T] = rule_T;
    grammar[E_dash] = rule_E_dash;
    grammar[T_dash] = rule_T_dash;
    grammar[F] = rule_F;
    cfg_ptr->set_grammar(grammar);
    cfg_ptr->set_start_symbol(E);

    // Building map of symbols and their corresponding productions.
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> sym_productions;
    sym_productions[E].push_back(prod_F1);
    sym_productions[E_dash].push_back(prod_E);
    sym_productions[E_dash].push_back(prod_E_dash);
    sym_productions[T].push_back(prod_E);
    sym_productions[T].push_back(prod_E_dash);
    sym_productions[T_dash].push_back(prod_T);
    sym_productions[T_dash].push_back(prod_T_dash);
    sym_productions[F].push_back(prod_T);
    sym_productions[F].push_back(prod_T_dash);
    cfg_ptr->set_cfg_symbol_productions(sym_productions);

    // Validating follow of non_terminals.
    std::map<std::string, std::set<std::string>> reference_sets;
    reference_sets["E"].insert(")");
    reference_sets["E"].insert("$");
    reference_sets["T"].insert(")");
    reference_sets["T"].insert("$");
    reference_sets["T"].insert("+");
    reference_sets["E'"].insert("$");
    reference_sets["E'"].insert(")");
    reference_sets["F"].insert(")");
    reference_sets["F"].insert("$");
    reference_sets["F"].insert("+");
    reference_sets["F"].insert("*");
    reference_sets["T'"].insert("+");
    reference_sets["T'"].insert(")");
    reference_sets["T'"].insert("$");
    auto follow_set_map = cfg_ptr->get_follow_set()->get_set_map();
    for (auto non_terminal : non_terminals) {
        auto curr_follow_set = follow_set_map[non_terminal.get_name()];
        std::set<std::string> curr_set;
        for (auto symbol : curr_follow_set) {
            curr_set.insert(symbol.get_name());
        }
        REQUIRE(curr_set == reference_sets[non_terminal.get_name()]);
    }
}
