#ifndef MARCHING_CUBES_RECONSTRUCTOR_H
#define MARCHING_CUBES_RECONSTRUCTOR_H

#include "surface_reconstructor.h"

class marchingCubesReconstructor : public surfaceReconstructor {
  public:
    marchingCubesReconstructor() {}

    triangleList reconstruct(const particleList& particles,
                             std::shared_ptr<levelSetFunction> levelSetPointer,
                             std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "marching_cubes_reconstructor.cpp"

#endif // MARCHING_CUBES_RECONSTRUCTOR_H
