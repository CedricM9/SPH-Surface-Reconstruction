#pragma once

class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}

    virtual double evaluate(double q) = 0;
};

