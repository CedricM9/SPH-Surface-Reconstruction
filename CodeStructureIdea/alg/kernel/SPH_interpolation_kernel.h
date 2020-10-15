#ifndef SPH_INTERPOLATION_KERNEL_H
#define SPH_INTERPOLATION_KERNEL_H

class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}

    virtual double evaluate(double q) = 0;
};

#endif // SPH_INTERPOLATION_KERNEL_H
