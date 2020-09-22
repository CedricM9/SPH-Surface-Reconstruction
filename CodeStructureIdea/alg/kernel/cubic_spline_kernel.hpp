#pragma once

#include "SPH_interpolation_kernel.hpp"

template <typename T>
class cubicSplineKernel : public SPHInterpolationKernel<T> {
  public:
    cubicSplineKernel();

    T evaluate(T q);
};

#include "cubic_spline_kernel.cpp"
