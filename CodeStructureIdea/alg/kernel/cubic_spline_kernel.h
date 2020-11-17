#ifndef CUBIC_SPLINE_KERNEL_H
#define CUBIC_SPLINE_KERNEL_H

#include<cmath>
#include<complex>

#include "particle.h"
#include "SPH_interpolation_kernel.h"

class cubicSplineKernel : public SPHInterpolationKernel {
  public:
    cubicSplineKernel();
    
    virtual void setRadius(float compactSupport);
    virtual float evaluate(float x, float y, float z, particle p2);
    virtual float evaluate(particle p1, particle p2);


  private:
    float a_;
    float h_;
};

#include "cubic_spline_kernel.cpp"

#endif // CUBIC_SPLINE_KERNEL_H


