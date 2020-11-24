#ifndef SPIKY_KERNEL_H
#define SPIKY_KERNEL_H

#include<cmath>

#include "CodeStructureIdea/data/particle.h"
#include "SPH_interpolation_kernel.h"

class spikyKernel : public SPHInterpolationKernel {
  public:
    spikyKernel();

    void setRadius(float compactSupport);
    double evaluate(float x, float y, float z, particle& p2);
    double evaluate(particle& p1, particle& p2);

  private:
    float a_;
    float h_;    
};

#include "spiky_kernel.cpp"

#endif // SPIKY_KERNEL_H
