#ifndef MARCHING_CUBES_RECONSTRUCTOR_H
#define MARCHING_CUBES_RECONSTRUCTOR_H

#include<cmath>

#include "surface_reconstructor.h"
#include "possibleGeometry.data"
#include "edgeIdentification.data"

class marchingCubesReconstructor : public surfaceReconstructor {
  public:
    marchingCubesReconstructor() {}

    void calculateDensities(std::vector<std::vector<unsigned int>>& nearestNeighbors, 
                            std::shared_ptr<SPHInterpolationKernel> kernelPointer,
                            particleList& particles,
                            float h);

    virtual triangleList reconstruct(graph& g,
                             particleList& particles,
                             const float h,
                             const float r,
                             std::shared_ptr<levelSetFunction> levelSetPointer,
                             std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "marching_cubes_reconstructor.cpp"

#endif // MARCHING_CUBES_RECONSTRUCTOR_H
