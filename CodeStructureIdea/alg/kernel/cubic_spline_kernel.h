#ifndef CUBIC_SPLINE_KERNEL_H
#define CUBIC_SPLINE_KERNEL_H

#include "SPH_interpolation_kernel.h"

class cubicSplineKernel : public SPHInterpolationKernel {
  public:
    cubicSplineKernel();

    double evaluate(double q);
};

#include "cubic_spline_kernel.cpp"

#endif // CUBIC_SPLINE_KERNEL_H
