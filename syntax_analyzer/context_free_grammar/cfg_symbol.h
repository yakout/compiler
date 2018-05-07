#ifndef COMPILER_CFG_SYMBOL_H
#define COMPILER_CFG_SYMBOL_H

#include <string>
#include <memory>
#include <functional>
#include <map>
#include <stack>
#include <vector>

enum cfg_symbol_type {
    TERMINAL,
    NON_TERMINAL,
    END_MARKER,
    SYNCH,
    ACTION,
    SYNTHESISED
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
    std::function<void(std::vector<cfg_symbol> &)> action;
    std::map<std::string, std::string> attributes;

public:
    cfg_symbol ();
    explicit cfg_symbol (cfg_symbol_type);
	explicit cfg_symbol (const std::string &, cfg_symbol_type);

    bool operator==(const cfg_symbol& other) const
    {
        return name == other.get_name() && type == other.get_type();
    }
    
    struct comparator {
        bool operator () (const cfg_symbol & sym_a, const cfg_symbol & sym_b) const {
            if (!sym_a.get_name ().compare (sym_b.get_name ())) 
                return true;
            return false;
        }
    };

    struct hasher {
        std::size_t operator () (const cfg_symbol & sym_a) const {
            return std::hash <std::string> () (sym_a.get_name ());
        }
    };


    void set_action(std::function<void(std::vector<cfg_symbol> &)> &action);
    void add_attribute(std::string name, std::string value);

    /** Getters **/
    const std::function<void(std::vector<cfg_symbol> &)> &get_action() const;
    std::string get_attribute(std::string name);

    std::string get_name () const;
    cfg_symbol_type get_type () const;
};

#endif //COMPILER_CFG_SYMBOL_H
