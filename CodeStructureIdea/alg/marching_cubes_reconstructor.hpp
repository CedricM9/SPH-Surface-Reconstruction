#pragma once

#include "surface_reconstructor.hpp"

class marchingCubesReconstructor : public surfaceReconstructor {
  public:
    marchingCubesReconstructor() {}

    triangleList reconstruct(const particleList& particles,
                             std::shared_ptr<levelSetFunction> levelSetPointer,
                             std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "marching_cubes_reconstructor.cpp"
