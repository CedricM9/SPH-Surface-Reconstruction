#pragma once

#include <memory>

#include "particle_list.hpp"
#include "triangle_list.hpp"

#include "level_set_function.hpp"
#include "compact_neighborhood_search.hpp"
#include "SPH_interpolation_kernel.hpp"

template <typename T>
class surfaceReconstructor {
  public:
    surfaceReconstructor() {}

    virtual triangleList<T> reconstruct(const particleList<T>& particles,
                                        std::shared_ptr<levelSetFunction<T>> levelSetPointer,
                                        std::shared_ptr<compactNeighborhoodSearch<T>> nSearchPointer,
                                        std::shared_ptr<SPHInterpolationKernel<T>>) = 0;
};

