#ifndef  NFA_CREATOR_H
#define  NFA_CREATOR_H

#include <stdio.h>

#include "finite_automata/finite_automata.h"

class NFA_Creator
{
public:
  NFA create_NFA (FILE* rules);
};

#endif // NFA_CREATOR_H
