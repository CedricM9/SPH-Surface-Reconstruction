#pragma once

#include "SPH_interpolation_kernel.hpp"

class cubicSplineKernel : public SPHInterpolationKernel {
  public:
    cubicSplineKernel();

    double evaluate(double q);
};

#include "cubic_spline_kernel.cpp"
