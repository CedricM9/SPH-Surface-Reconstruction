#ifndef LEVEL_SET_FUNCTION_H
#define LEVEL_SET_FUNCTION_H

#include "particle_list.h"

class levelSetFunction {
  public:
    levelSetFunction() {}

    virtual double evaluate(const particleList& list) = 0;
};

#endif // LEVEL_SET_FUNCTION_H
