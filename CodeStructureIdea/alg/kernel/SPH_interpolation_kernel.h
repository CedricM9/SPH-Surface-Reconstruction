#ifndef SPH_INTERPOLATION_KERNEL_H
#define SPH_INTERPOLATION_KERNEL_H

#include "particle.h"

class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}

    virtual void setRadius(float compactSupport);
    virtual float evaluate(particle& x, particle& xPrime, int h) = 0;
};

#endif // SPH_INTERPOLATION_KERNEL_H
