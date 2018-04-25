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

    virtual /** Getters **/
    cfg_symbol get_lhs_symbol ();

    virtual std::vector <cfg_symbol> get_symbols ();
};

#endif //COMPILER_CFG_PRODUCTION_H
