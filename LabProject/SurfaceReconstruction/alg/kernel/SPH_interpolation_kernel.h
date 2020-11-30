#ifndef SPH_INTERPOLATION_KERNEL_H
#define SPH_INTERPOLATION_KERNEL_H

#include "particle.h"

class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}
    virtual ~SPHInterpolationKernel() = default;

    virtual void setRadius(float compactSupport) = 0;
    virtual float evaluate(float x, float y, float z, particle xPrime) = 0;
    virtual float evaluate(particle x, particle xPrime) = 0;
};

#endif // SPH_INTERPOLATION_KERNEL_H
