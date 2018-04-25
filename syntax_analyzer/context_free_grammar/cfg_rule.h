#ifndef COMPILER_CFG_RULE_H
#define COMPILER_CFG_RULE_H

#include "cfg_production.h"
#include <string>
#include <vector>

class cfg_rule {
private:
    /** Example: A -> a | b c | d
     *  lhs_symbol: A
     *  production_symbols: {{a}, {b, c}, {d}}
     */
    cfg_symbol lhs_symbol;
    std::vector <cfg_production> productions;
public:
    cfg_rule ();
    explicit cfg_rule (cfg_symbol &, std::vector <cfg_production> &);
    
    /** Getters **/
    cfg_symbol get_lhs_symbol ();
    std::vector <cfg_production> get_productions ();
};

#endif //COMPILER_CFG_RULE_H