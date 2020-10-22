#ifndef SPIKY_KERNEL_H
#define SPIKY_KERNEL_H

#include "SPH_interpolation_kernel.h"

class spikyKernel : public SPHInterpolationKernel {
  public:
    spikyKernel();

    double evaluate(double q);
};

#include "spiky_kernel.cpp"

#endif // SPIKY_KERNEL_H
