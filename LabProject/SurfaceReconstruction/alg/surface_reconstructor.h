#ifndef SURFACE_RECONSTRUCTOR_H
#define SURFACE_RECONSTRUCTOR_H

#include <memory>
#include <vector>

#include "particle_list.h"
#include "triangle_list.h"
#include "graph.h"
#include "level_set_function.h"


/** \class surfaceReconstructor
 * \brief Virtual class for the reconstruction process
 * \details This virtual class the base of the derived marchingCubesReconstructor
 */
class surfaceReconstructor {
  public:
    surfaceReconstructor() {}
    virtual ~surfaceReconstructor() = default;

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
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // SURFACE_RECONSTRUCTOR_H
