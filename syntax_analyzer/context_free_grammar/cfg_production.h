#ifndef COMPILER_CFG_PRODUCTION_H
#define COMPILER_CFG_PRODUCTION_H

#include "cfg_symbol.h"
#include <vector>

class cfg_production
{
private:
    /** Example: A -> B a e A
     *  lhs_symbol: A
     *  production_symbols: {B, a, e, A}
     */
    cfg_symbol lhs_symbol;
    std::vector <cfg_symbol> production_symbols;
public:
    cfg_production ();
    explicit cfg_production (cfg_symbol &, std::vector <cfg_symbol> &);

    void set_lhs_symbol (cfg_symbol &);
    void add_symbol (cfg_symbol &);

    /**
     * removes the first symbol in the production.
     */
    void pop_first_symbol();
    /**
     * checks if the production has the given symbol.
     * @returns index of the symbol if found, otherwise returns -1.
     */
    int find(cfg_symbol);

    /** Getters **/
    virtual cfg_symbol get_lhs_symbol () const;
    virtual std::string to_string();
    virtual std::string get_rhs_as_string();
    virtual std::vector <cfg_symbol> get_symbols () const;
};

#endif //COMPILER_CFG_PRODUCTION_H
