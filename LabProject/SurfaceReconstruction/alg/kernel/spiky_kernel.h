#ifndef SPIKY_KERNEL_H
#define SPIKY_KERNEL_H

#include<cmath>

#include "particle.h"
#include "SPH_interpolation_kernel.h"

/** \class spikyKernel
 * \brief Spiky kernel (not fully functioning)
 * \details Derived class consisting of the specific SPH Interpolation kernel, spiky.
 * We have not gotten this to work in the reconstruction
 */
class spikyKernel : public SPHInterpolationKernel {
  public:
    spikyKernel();

    /** \brief Function that sets the radius of the kernel
     * \details This function sets the radius which dictates which neighbors are included
     * \param compactSupport The radius
     */
    void setRadius(float compactSupport);

    /** \brief Function evaluates the kernel function given one coordinate and one particle
     * \details This function evaluates the kernel based on the particles proximity to the 
     * coordinate (x,y,z)
     * \param x x-coordinate
     * \param y y-coordinate
     * \param z z-coordinate
     * \param xPrime Particle which is being compared to the coordinate
     */
    double evaluate(float x, float y, float z, particle& p2);

    /** \brief Function evaluates the kernel function given two particles
     * \details This function evaluates the kernel based on proximity between the two particles
     * \param x First particle
     * \param xPrime Particle which is being compared the first particle
     */  
    double evaluate(particle& p1, particle& p2);

  private:
    float a_;
    float h_;    
};

#include "spiky_kernel.cpp"

#endif // SPIKY_KERNEL_H
