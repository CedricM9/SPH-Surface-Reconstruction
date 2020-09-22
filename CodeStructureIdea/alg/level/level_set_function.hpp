#pragma once

#include "particle_list.hpp"

template <typename T>
class levelSetFunction {
  public:
    levelSetFunction() {}

    virtual T evaluate(const particleList<T>& list) = 0;
};

