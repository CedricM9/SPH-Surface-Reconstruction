#ifndef MARCHING_CUBES_RECONSTRUCTOR_H
#define MARCHING_CUBES_RECONSTRUCTOR_H

#include<cmath>

#include "surface_reconstructor.h"
#include "possibleGeometry.data"
#include "edgeIdentification.data"

/** \class marchingCubesReconstructor
 * \brief Class for reconstructing the surface mesh
 * \details This class fully reconstructs the surface mesh with the given parameters.
 * It calls all required subsequent functions
 */
class marchingCubesReconstructor : public surfaceReconstructor {
  public:
    marchingCubesReconstructor() {}

    /** \brief Calculates the particle densitiy of each particle of the simulation
     * \details This function determines how many particles surround a specified particle
     * and returns a value to represent this density
     * \param nearestNeighbors Contains the neighbors of each particle
     * \param kernelPointer Pointer to the SPH Interpolation Kernel
     * \param particles List of all particles
     * \param h Also referred to as smoothing lenght. Required by the SPH interpolation
     */
    void calculateDensities(std::vector<std::vector<unsigned int>>& nearestNeighbors, 
                            std::shared_ptr<SPHInterpolationKernel> kernelPointer,
                            particleList& particles,
                            float h);
  
    /** \brief Generates entire surface mesh
     * \details This function takes care of the entire reconstruction process for a single frame
     * \param g Graph which has been created for the simulation data
     * \param particles List of all particles
     * \param smoothingLength Also referred to as h. Required by the SPH Interpolation
     * \param compactSupport The radius for the neighborhood search. Should be 2*h
     * \param iso Value to exclude outlying particles
     * \param levelSetPointer Pointer to the level set function
     * \param nSearchPointer Pointer to the compact support neighborhood search
     * \param kernelPointer Pointer to the specified SPH Interpolation Kernel
     */
    virtual triangleList reconstruct(graph& g,
                             particleList& particles,
                             const float smoothingLength,
                             const float compactSupport,
                             const float iso,
                             std::shared_ptr<levelSetFunction> levelSetPointer,
                             std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "marching_cubes_reconstructor.cpp"

#endif // MARCHING_CUBES_RECONSTRUCTOR_H
