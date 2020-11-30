#ifndef LEVEL_SET_FUNCTION_H
#define LEVEL_SET_FUNCTION_H

#include<vector>
#include<memory>

#include "compact_neighborhood_search.h"
#include "SPH_interpolation_kernel.h"
#include "particle_list.h"

/** \class levelSetFunction
 * \brief Virtual class off of which the level set function is derived
 * \details Base class for the derived Level set function
 */
class levelSetFunction {
  public:
    levelSetFunction() {}
    virtual ~levelSetFunction() = default;

  
    /** \brief Evaluates the level set value
     * \details This function checks if a given point is within a surface by referencing
     * all of the particles within the radius of the point
     * \param list List of every particle
     * \param x x-coordinate of the point of calculation
     * \param y y-coordinate of the point of calculation
     * \param z z-coordinate of the point of calculation
     * \param h Smoothing value required for the interpolation kernel
     * \param c iso value which removes points that are less likely to be inside the fluid
     * \param r Compact support radius
     * \param nSearchPointer Pointer to the Compact Support Neighborhood Search
     * \param kernelPointer Pointer to the SPH Interpolation Kernel
     */
    virtual double evaluate(particleList& list, 
                    float x,
                    float y,
                    float z,
                    float h,
                    float c,
                    float r,
                    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                    std::shared_ptr<SPHInterpolationKernel> kernelPointer) = 0;
};

#endif // LEVEL_SET_FUNCTION_H
