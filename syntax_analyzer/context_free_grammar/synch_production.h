#ifndef COMPILER_CFG_SYNCH_PRODUCTION_H
#define COMPILER_CFG_SYNCH_PRODUCTION_H

#include "cfg_symbol.h"
#include "cfg_production.h"
#include <vector>

class synch_production : public cfg_production
{
private:
    /** Example: A -> B a e A
     *  lhs_symbol: A
     *  production_symbols: {B, a, e, A}
     */
    cfg_symbol lhs_symbol;
    std::vector <cfg_symbol> production_symbols;
public:
    synch_production ();

    /** Getters **/
    cfg_symbol get_lhs_symbol () const;
    std::vector <cfg_symbol> get_symbols () const;
};


#endif //COMPILER_CFG_SYNCH_PRODUCTION_H
