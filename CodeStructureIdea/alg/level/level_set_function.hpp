#pragma once

#include "particle_list.hpp"

class levelSetFunction {
  public:
    levelSetFunction() {}

    virtual double evaluate(const particleList& list) = 0;
};

