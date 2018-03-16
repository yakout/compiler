#ifndef NFA_DFA_CONVERTER_H
#define NFA_DFA_CONVERTER_H

#include "finite_automata/finite_automata.h"

class NFA_DFA_Converter
{
public:
  DFA convert_NFA_to_DFA (NFA nfa);
};

#endif // NFA_DFA_CONVERTER_H
