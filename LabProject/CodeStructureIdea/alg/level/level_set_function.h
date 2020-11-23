#ifndef LEVEL_SET_FUNCTION_H
#define LEVEL_SET_FUNCTION_H

#include<vector>
#include<memory>

#include "CodeStructureIdea/alg/nsearch/compact_neighborhood_search.h"
#include "CodeStructureIdea/alg/kernel/SPH_interpolation_kernel.h"
#include "CodeStructureIdea/data/particle_list.h"

class levelSetFunction {
  public:
    levelSetFunction() {}
    virtual ~levelSetFunction() = default;

    virtual double evaluate(particleList& list, 
                    float x,
                    float y,
                    float z,
                    float h,
                    float c,
                    float r,
                    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                    std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // LEVEL_SET_FUNCTION_H
