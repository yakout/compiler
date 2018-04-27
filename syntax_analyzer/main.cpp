#include <iostream>
#include "predictive_parser.h"

int main (int argc, char *argv[]) {
    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$(END_MARKER);

    // LHS NON_TERMINALS SYMBOLS
    cfg_symbol S("S", NON_TERMINAL);
    cfg_symbol E("E", NON_TERMINAL);
    cfg_symbol C("C", NON_TERMINAL);

    // TERMINALS SYMBOLS
    cfg_symbol a("a", TERMINAL);
    cfg_symbol b("b", TERMINAL);
    cfg_symbol e("e", TERMINAL);
    cfg_symbol i("i", TERMINAL);
    cfg_symbol t("t", TERMINAL);

    // FILL THE PRODUCTIONS VECTORS **********************************
    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> S_prod_vector1;
    std::vector<cfg_symbol> S_prod_vector2;

    std::vector<cfg_symbol> E_prod_vector;

    std::vector<cfg_symbol> C_prod_vector;

    eps_vector.push_back(eps);

    // S -> iCtSE
    S_prod_vector1.push_back(i);
    S_prod_vector1.push_back(C);
    S_prod_vector1.push_back(t);
    S_prod_vector1.push_back(S);
    S_prod_vector1.push_back(E);

    // S -> a
    S_prod_vector2.push_back(a);

    // E -> eS
    E_prod_vector.push_back(e);
    E_prod_vector.push_back(S);

    // C -> b
    C_prod_vector.push_back(b);

    // ****************************************************************

    // CONSTRUCT PRODUCTION
    cfg_production prod_S1(S, S_prod_vector1);
    cfg_production prod_S2(S, S_prod_vector2);
    cfg_production prod_E1(E, E_prod_vector);
    cfg_production prod_E2(E, eps_vector);
    cfg_production prod_C(C, C_prod_vector);

    std::shared_ptr<cfg> cfg_ptr = std::make_shared<cfg>(cfg ());

    // Building non_terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> non_terminals;
    non_terminals.insert(E);
    non_terminals.insert(S);
    non_terminals.insert(C);
    cfg_ptr->set_non_terminals(non_terminals);

    // Building terminals
    std::unordered_set<cfg_symbol, cfg_symbol::hasher, cfg_symbol::comparator> terminals;
    terminals.insert(eps);
    terminals.insert(a);
    terminals.insert(b);
    terminals.insert(e);
    terminals.insert(i);
    terminals.insert(t);
    cfg_ptr->set_terminals(terminals);

    // Building grammar
    std::unordered_map <cfg_symbol, cfg_rule
            , cfg_symbol::hasher, cfg_symbol::comparator> grammar;
    std::vector<cfg_production> S_productions;
    std::vector<cfg_production> E_productions;
    std::vector<cfg_production> C_productions;

    S_productions.push_back(prod_S1);
    S_productions.push_back(prod_S2);
    E_productions.push_back(prod_E1);
    E_productions.push_back(prod_E2);
    C_productions.push_back(prod_C);

    // Building rules
    cfg_rule rule_S(S, S_productions);
    cfg_rule rule_E(E, E_productions);
    cfg_rule rule_C(C, C_productions);


    grammar[S] = rule_S;
    grammar[E] = rule_E;
    grammar[C] = rule_C;
    cfg_ptr->set_grammar(grammar);
    cfg_ptr->set_start_symbol(S);

    // Building map of symbols and their corresponding productions.
    std::unordered_map <cfg_symbol, std::vector <cfg_production>, cfg_symbol::hasher
            , cfg_symbol::comparator> sym_productions;
    sym_productions[S].push_back(prod_S1);
    sym_productions[S].push_back(prod_E1);
    sym_productions[E].push_back(prod_S1);
    sym_productions[C].push_back(prod_S1);
    cfg_ptr->set_cfg_symbol_productions(sym_productions);

    // Printing first set to console.
    auto first_set_map = cfg_ptr->get_first_set()->get_set_map();
    std::vector<cfg_symbol> all_symbols;
    all_symbols.insert(all_symbols.end(), terminals.begin(), terminals.end());
    all_symbols.insert(all_symbols.end(), non_terminals.begin(), non_terminals.end());
    for (auto symbol : all_symbols) {
        auto curr_set = first_set_map[symbol.get_name()];
        std::cout << "FIRST(" << symbol.get_name() << ") = {";
        int cnt = 0;
        for (auto sym : curr_set) {
            if (cnt == curr_set.size() - 1) {
                std::cout << sym.first.get_name();
            } else {
                std::cout << sym.first.get_name() << ",";
            }
            cnt++;
        }
        std::cout << "}\n";
    }
    std::cout << "\n\n";

    // Printing follow set to console.
    auto follow_set_map = cfg_ptr->get_follow_set()->get_set_map();
    for (auto non_terminal : non_terminals) {
        auto curr_set = follow_set_map[non_terminal.get_name()];
        std::cout << "FOLLOW(" << non_terminal.get_name() << ") = {";
        int cnt = 0;
        for (auto symbol : curr_set) {
            if (cnt != curr_set.size() - 1) {
                std::cout << symbol.get_name() << ",";
            } else {
                std::cout << symbol.get_name();
            }
            cnt++;
        }
        std::cout << "}\n";
        std::cout << "size = " << curr_set.size() << "\n";
    }
}
