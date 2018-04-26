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

    table[{"E", "id"}] = prod_E;
    table[{"E", "("}] = prod_E;

    table[{"E'", "+"}] = prod_E_dash;
    table[{"E'", ")"}] = prod_E_dash_eps;
    table[{"E'", "$"}] = prod_E_dash_eps;

    table[{"T", "id"}] = prod_T;
    table[{"T", "("}] = prod_T;

    table[{"T'", "+"}] = prod_T_dash_eps;
    table[{"T'", "*"}] = prod_T_dash;
    table[{"T'", ")"}] = prod_T_dash_eps;
    table[{"T'", "$"}] = prod_T_dash_eps;

    table[{"F", "("}] = prod_F1;
    table[{"F", "id"}] = prod_F2;

    std::shared_ptr<parsing_table> p_table = std::make_shared<parsing_table>(table);

    p_table->draw("parsing_table.txt");
}