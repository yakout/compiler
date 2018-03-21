#ifndef  NFA_CREATOR_H
#define  NFA_CREATOR_H

#include <stdio.h>

#include "finite_automata/finite_automata.h"
#include "finite_automata/nfa.h"

class nfa_creator
{
public:
  nfa create_nfa (FILE* rules);
};

#endif // NFA_CREATOR_H
