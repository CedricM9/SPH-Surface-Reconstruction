#ifndef DIMENSIONLESS_LEVEL_SET_FUNCTION_H
#define DIMENSIONLESS_LEVEL_SET_FUNCTION_H

#include<memory>
#include<vector>

#include "level_set_function.h"

class dimensionlessLevelSetFunction : public levelSetFunction {
  public:
    dimensionlessLevelSetFunction();

    double evaluate(particleList& list, 
                    particle& p, 
                    float h,
                    float c,
                    float r,
                    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                    std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "dimensionless_level_set_function.cpp"

#endif // DIMENSIONLESS_LEVEL_SET_FUNCTION_H
