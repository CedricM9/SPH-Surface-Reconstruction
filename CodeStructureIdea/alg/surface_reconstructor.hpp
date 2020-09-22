#pragma once

#include <memory>

#include "particle_list.hpp"
#include "triangle_list.hpp"

#include "level_set_function.hpp"
#include "compact_neighborhood_search.hpp"
#include "SPH_interpolation_kernel.hpp"

class surfaceReconstructor {
  public:
    surfaceReconstructor() {}

    virtual triangleList reconstruct(const particleList& particles,
                                     std::shared_ptr<levelSetFunction> levelSetPointer,
                                     std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                                     std::shared_ptr<SPHInterpolationKernel>) = 0;
};

