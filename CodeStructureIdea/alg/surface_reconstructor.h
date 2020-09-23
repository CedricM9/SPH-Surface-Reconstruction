#ifndef SURFACE_RECONSTRUCTOR_H
#define SURFACE_RECONSTRUCTOR_H

#include <memory>

#include "particle_list.h"
#include "triangle_list.h"

#include "level_set_function.h"
#include "compact_neighborhood_search.h"
#include "SPH_interpolation_kernel.h"

class surfaceReconstructor {
  public:
    surfaceReconstructor() {}

    virtual triangleList reconstruct(const particleList& particles,
                                     std::shared_ptr<levelSetFunction> levelSetPointer,
                                     std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                                     std::shared_ptr<SPHInterpolationKernel>) = 0;
};

#endif // SURFACE_RECONSTRUCTOR_H