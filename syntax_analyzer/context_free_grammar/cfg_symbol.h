#ifndef COMPILER_CFG_SYMBOL_H
#define COMPILER_CFG_SYMBOL_H

#include <string>
#include <memory>

enum cfg_symbol_type {
    TERMINAL,
    NON_TERMINAL,
    END_MARKER,
    SYNCH
};

class cfg_production;

class cfg_symbol {
private:
    /** Example: A
     * name: A
     * type: NON_TERMINAL
     */
    std::string name;
    cfg_symbol_type type;
    std::shared_ptr<cfg_production> parent_prod;
public:
    const std::shared_ptr<cfg_production> &get_parent_prod() const;

    void set_parent_prod(const std::shared_ptr<cfg_production> &parent_prod);

public:
    cfg_symbol ();
    explicit cfg_symbol (cfg_symbol_type);
	explicit cfg_symbol (std::string &, cfg_symbol_type);
    
    /** Getters **/
    std::string get_name ();
    cfg_symbol_type get_type ();
};

#endif //COMPILER_CFG_SYMBOL_H
