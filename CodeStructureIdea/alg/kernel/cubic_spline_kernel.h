#ifndef CUBIC_SPLINE_KERNEL_H
#define CUBIC_SPLINE_KERNEL_H

#include<cmath>
#include<complex>

#include "particle.h"
#include "SPH_interpolation_kernel.h"

class cubicSplineKernel : public SPHInterpolationKernel {
  public:
    cubicSplineKernel();
    
    void setRadius(float compactSupport);
    double evaluate(particle& p1, particle& p2);


  private:
    float a_;
    float h_;
};

#include "cubic_spline_kernel.cpp"

#endif // CUBIC_SPLINE_KERNEL_H


