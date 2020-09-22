#pragma once

#include "surface_reconstructor.hpp"

template <typename T>
class marchingCubesReconstructor : public surfaceReconstructor<T> {
  public:
    marchingCubesReconstructor() {}

    triangleList<T> reconstruct(const particleList<T>& particles,
                                std::shared_ptr<levelSetFunction<T>> levelSetPointer,
                                std::shared_ptr<compactNeighborhoodSearch<T>> nSearchPointer,
                                std::shared_ptr<SPHInterpolationKernel<T>> kernelPointer);
};

#include "marching_cubes_reconstructor.cpp"
