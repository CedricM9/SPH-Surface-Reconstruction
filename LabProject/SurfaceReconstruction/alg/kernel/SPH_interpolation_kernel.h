#ifndef SPH_INTERPOLATION_KERNEL_H
#define SPH_INTERPOLATION_KERNEL_H

#include "particle.h"

/** \class SPHInterpolationKernel
 * \brief Virtual Class from which an SPH kernel can be implemented
 * \details This virtual class is used to derive different interpolation kernels
 */
class SPHInterpolationKernel {
  public:
    SPHInterpolationKernel() {}
    virtual ~SPHInterpolationKernel() = default;

  /** \brief Function that sets the radius of the kernel
     * \details This function sets the radius which dictates which neighbors are included
     * \param compactSupport The radius
     */
    virtual void setRadius(float compactSupport) = 0;

  /** \brief Function evaluates the kernel function given one coordinate and one particle
     * \details This function evaluates the kernel based on the particles proximity to the 
     * coordinate (x,y,z)
     * \param x x-coordinate
     * \param y y-coordinate
     * \param z z-coordinate
     * \param xPrime Particle which is being compared to the coordinate
     */
    virtual float evaluate(float x, float y, float z, particle xPrime) = 0;

    /** \brief Function evaluates the kernel function given two particles
     * \details This function evaluates the kernel based on proximity between the two particles
     * \param x First particle
     * \param xPrime Particle which is being compared the first particle
     */
    virtual float evaluate(particle x, particle xPrime) = 0;
};


#endif // SPH_INTERPOLATION_KERNEL_H
