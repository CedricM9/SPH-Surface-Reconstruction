#ifndef MARCHING_CUBES_RECONSTRUCTOR_H
#define MARCHING_CUBES_RECONSTRUCTOR_H

#include<cmath>

#include "surface_reconstructor.h"
#include "possibleGeometry.data"
#include "edgeIdentification.data"


/** \class marchingCubesReconstructor
 * \brief Handles the entire reconstruction process
 * \details This class is given all of the required parameters as well as a grid 
 * and calculates the mesh surface.
 */
class marchingCubesReconstructor : public surfaceReconstructor {
  public:
    marchingCubesReconstructor() {}

    /** \brief Calculates the density of particles as each particle
     * \details This function takes in a vector of neighbors for each particle and runs 
     * uses the kernel function to determine how densley populated the region is
     * \param nearestNeighbors A vector which includes each particle's neighbors
     * \param kernelPointer Pointer to the specified SPH Interpolation Kernel
     * \particles A list that consists of all particles
     * \h Smoothing length required for the interpolation kernel
     */
    void calculateDensities(std::vector<std::vector<unsigned int>>& nearestNeighbors, 
                            std::shared_ptr<SPHInterpolationKernel> kernelPointer,
                            particleList& particles,
                            float h);
  
    /** \brief Reconstructs the surface Mesh
     * \details This function recreates the entire surface mesh with the given parameters
     * \param g The graph which is being projected over the particles
     * \param particles List of all particles
     * \param smoothingLength Also referred to as h, should be 0.5*compact Support
     * \param compactSupport Radius for the neighborhood search. Should be 2*h
     * \param iso Value that shifts the iso-surface to ignore points which are less likely
     * to be within the fluid. Meaningful value should be between 0 and 1
     * \param levelSetPointer Pointer to the level set function
     * \param nSearchPonter Pointer to the compact neighborhood search
     * \param kernelPointer Pointer to the specific SPH Interpolation Kernel
     * \return Returns a triangleList which includes the coordinates and indices of the mesh's triangles
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
