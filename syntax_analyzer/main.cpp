#include <iostream>
#include "predictive_parser.h"

int main (int argc, char *argv[]) {
    std::vector<cfg_symbol> eps_vector;

    std::vector<cfg_symbol> E_prod_vector;
    std::vector<cfg_symbol> E_dash_prod_vector;

    std::vector<cfg_symbol> T_prod_vector;
    std::vector<cfg_symbol> T_dash_prod_vector;

    std::vector<cfg_symbol> F_prod_vector1;
    std::vector<cfg_symbol> F_prod_vector2;


    // SPECIAL SYMBOLS
    cfg_symbol eps(EPS, TERMINAL);
    cfg_symbol s_$("$", END_MARKER);

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


    // TESTING FIRST SETs
    std::shared_ptr<cfg> cfg_ptr = std::make_shared<cfg>(cfg ());
    std::vector<cfg_symbol> non_terminals;
    non_terminals.push_back(E);
    non_terminals.push_back(E_dash);
    non_terminals.push_back(T_dash);
    non_terminals.push_back(T);
    non_terminals.push_back(F);
    cfg_ptr->set_non_terminals(non_terminals);

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

//    auto gram = cfg_ptr->get_grammar();
//    for (auto entry : gram) {
//        std::cout << entry.first.get_name() << "\n";
//        auto rule = entry.second;
//        std::cout << "Current rule's lhs = " << rule.get_lhs_symbol().get_name() << "\n";
//        auto productions = rule.get_productions();
//        for (auto pro : productions) {
//            for (auto sym : pro.get_symbols()) {
//                std::cout << sym.get_name() << "\n";
//            }
//        }
//        std::cout << "\n\n";
//    }
//    std::cout << "hi\t\t\t" << gram[E].get_lhs_symbol().get_name() << "\n\n\n\n\n\n";
    auto first_set_map = cfg_ptr->get_first_set()->get_set_map();
    for (auto non_terminal : non_terminals) {
        auto curr_set = first_set_map[non_terminal.get_name()];
        std::cout << "FIRST(" << non_terminal.get_name() << ") = {";
        for (auto symbol : curr_set) {
            std::cout << symbol.first.get_name() << ",";
        }
        std::cout << "}\n";
//        std::cout << curr_set.size() << "\n";
    }
    std::cout << "\n\n";

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
    std::vector <cfg_symbol> terminals;
    terminals.push_back(eps);
    terminals.push_back(plus);
    terminals.push_back(multiplication);
    terminals.push_back(left_paren);
    terminals.push_back(right_paren);
    terminals.push_back(id);
    cfg_ptr->set_terminals(terminals);

    auto follow_set_map = cfg_ptr->get_follow_set()->get_set_map();
    for (auto non_terminal : non_terminals) {
        auto curr_set = follow_set_map[non_terminal.get_name()];
        std::cout << "FOLLOW(" << non_terminal.get_name() << ") = {";
        for (auto symbol : curr_set) {
            std::cout << symbol.first.get_name() << ",";
        }
        std::cout << "}\n";
        std::cout << "size = " << curr_set.size() << "\n";
    }
    std::cout << "\n\n";

}


//    E -> TE’
//    E’ -> +TE’ | eps
//    T -> FT’
//    T’ -> *FT’ | eps
//    F -> (E) | id

//    FIRST(F) = {(,id}
//    FIRST(T’) = {*, eps}
//    FIRST(T) = {(,id}
//    FIRST(E’) = {+, eps}
//    FIRST(E) = {(,id}

//    FIRST(TE’) = {(,id}
//    FIRST(+TE’ ) = {+}
//    FIRST(eps) = {eps}
//    FIRST(FT’) = {(,id}
//    FIRST(*FT’) = {*}
//    FIRST(eps) = {eps}
//    FIRST((E)) = {(}
//    FIRST(id) = {id}