#ifndef DIMENSIONLESS_LEVEL_SET_FUNCTION_H
#define DIMENSIONLESS_LEVEL_SET_FUNCTION_H

#include "level_set_function.h"

class dimensionlessLevelSetFunction : public levelSetFunction {
  public:
    dimensionlessLevelSetFunction();

    virtual double evaluate(const particleList& list);
};

#include "dimensionless_level_set_function.cpp"

#endif // DIMENSIONLESS_LEVEL_SET_FUNCTION_H
