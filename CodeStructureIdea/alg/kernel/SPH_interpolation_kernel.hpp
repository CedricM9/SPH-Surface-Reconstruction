#pragma once

template <typename T>
class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}

    virtual T evaluate(T q) = 0;
};

