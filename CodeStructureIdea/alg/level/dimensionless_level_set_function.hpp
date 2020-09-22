#pragma once

#include "level_set_function.hpp"

template <typename T>
class dimensionlessLevelSetFunction : public levelSetFunction<T> {
  public:
    dimensionlessLevelSetFunction();

    virtual T evaluate(const particleList<T>& list);
};

#include "dimensionless_level_set_function.cpp"
