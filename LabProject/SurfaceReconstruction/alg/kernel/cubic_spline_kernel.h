#ifndef CUBIC_SPLINE_KERNEL_H
#define CUBIC_SPLINE_KERNEL_H

#include<complex>

#include "particle.h"
#include "SPH_interpolation_kernel.h"

/** \class cubicSplineKernel
 * \brief cubic spline SPH Interpolation Kernel
 * \details Derived class consisting of the specific SPH Interpolation kernel, cubic spline
 */
class cubicSplineKernel : public SPHInterpolationKernel {
  public:
    cubicSplineKernel();
  
    /** \brief Function that sets the radius of the kernel
     * \details This function sets the radius which dictates which neighbors are included
     * \param compactSupport The radius
     */
    virtual void setRadius(float compactSupport);
  
    /** \brief Function evaluates the kernel function given one coordinate and one particle
     * \details This function evaluates the kernel based on the particles proximity to the 
     * coordinate (x,y,z)
     * \param x x-coordinate
     * \param y y-coordinate
     * \param z z-coordinate
     * \param xPrime Particle which is being compared to the coordinate
     */
    virtual float evaluate(float x, float y, float z, particle p2);
  
    /** \brief Function evaluates the kernel function given two particles
     * \details This function evaluates the kernel based on proximity between the two particles
     * \param x First particle
     * \param xPrime Particle which is being compared the first particle
     */  
    virtual float evaluate(particle p1, particle p2);
  

  private:
    float a_;
    float h_;
};

#include "cubic_spline_kernel.cpp"

#endif // CUBIC_SPLINE_KERNEL_H


