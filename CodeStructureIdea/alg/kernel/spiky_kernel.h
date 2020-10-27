#ifndef SPIKY_KERNEL_H
#define SPIKY_KERNEL_H

#include<cmath>

#include "particle.h"
#include "SPH_interpolation_kernel.h"

class spikyKernel : public SPHInterpolationKernel {
  public:
    spikyKernel();

    void setRadius(float compactSupport);
    double evaluate(particle& p1, particle& p2);

  private:
    float a_;
    float h_;    
};

#include "spiky_kernel.cpp"

#endif // SPIKY_KERNEL_H
