#pragma once

#include "level_set_function.hpp"

class dimensionlessLevelSetFunction : public levelSetFunction {
  public:
    dimensionlessLevelSetFunction();

    virtual double evaluate(const particleList& list);
};

#include "dimensionless_level_set_function.cpp"
