#ifndef SURFACE_RECONSTRUCTOR_H
#define SURFACE_RECONSTRUCTOR_H

#include <memory>
#include <vector>

#include "CodeStructureIdea/data/particle_list.h"
#include "CodeStructureIdea/data/triangle_list.h"
#include "CodeStructureIdea/data/graph.h"
#include "CodeStructureIdea/alg/level/level_set_function.h"

//#include "level_set_function.h"
//#include "compact_neighborhood_search.h"
//#include "SPH_interpolation_kernel.h"

class surfaceReconstructor {
  public:
    surfaceReconstructor() {}
    virtual ~surfaceReconstructor() = default;

    /*virtual triangleList reconstruct(const particleList& particles,
                                     std::shared_ptr<levelSetFunction> levelSetPointer,
                                     std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                                     std::shared_ptr<SPHInterpolationKernel>) = 0; */
    virtual triangleList reconstruct(graph& g,
                             particleList& particles,
                             const float h,
                             const float r,
                             std::shared_ptr<levelSetFunction> levelSetPointer,
                             std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // SURFACE_RECONSTRUCTOR_H
