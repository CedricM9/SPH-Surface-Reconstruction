#pragma once

#include "particle_list.h"

class levelSetFunction {
  public:
    levelSetFunction() {}

    virtual double evaluate(const particleList& list) = 0;
};

