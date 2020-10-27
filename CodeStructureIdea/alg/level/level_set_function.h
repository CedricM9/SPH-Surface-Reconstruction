#ifndef LEVEL_SET_FUNCTION_H
#define LEVEL_SET_FUNCTION_H

#include<vector>
#include<memory>

#include "compact_neighborhood_search.h"
#include "SPH_interpolation_kernel.h"
#include "particle_list.h"

class levelSetFunction {
  public:
    levelSetFunction() {}

    virtual double evaluate(particleList& list, 
                    particle& p, 
                    float h,
                    float c,
                    float r,
                    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                    std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // LEVEL_SET_FUNCTION_H
