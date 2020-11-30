#ifndef SURFACE_RECONSTRUCTOR_H
#define SURFACE_RECONSTRUCTOR_H

#include <memory>
#include <vector>

#include "particle_list.h"
#include "triangle_list.h"
#include "graph.h"
#include "level_set_function.h"

/** \class surfaceReconstructor
 * \brief Virtual class off of which the surface reconstructor is derived
 * \details This is the virtual class which is used for the reconstruction process
 */
class surfaceReconstructor {
  public:
    surfaceReconstructor() {}
    virtual ~surfaceReconstructor() = default;

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
                             std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // SURFACE_RECONSTRUCTOR_H
