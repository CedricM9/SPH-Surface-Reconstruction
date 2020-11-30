#ifndef DIMENSIONLESS_LEVEL_SET_FUNCTION_H
#define DIMENSIONLESS_LEVEL_SET_FUNCTION_H

#include<memory>
#include<vector>
#include<cmath>

#include "level_set_function.h"


/** \class dimensionlessLevelSetFunction
 * \brief Level Set Function which determines the iso-surface
 * \details Implementation of the level set function which calculates whether
 * the point in question is inside or outside of the fluid
 */
class dimensionlessLevelSetFunction : public levelSetFunction {
  public:
    dimensionlessLevelSetFunction();

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
    double evaluate(particleList& list, 
                    float x,
                    float y,
                    float z,
                    float h,
                    float c,
                    float r,
                    std::shared_ptr<compactNeighborhoodSearch> nSearchPointer,
                    std::shared_ptr<SPHInterpolationKernel> kernelPointer);
};

#include "dimensionless_level_set_function.cpp"

#endif // DIMENSIONLESS_LEVEL_SET_FUNCTION_H
