#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>

/** \class particle
 * \brief Data structure for particles existing of 3D coordinates and a density
 * \details This class provides all neccessary operations for accessing and storing particle data.
 */
class particle {
  public:
    particle();
    particle(float x, float y, float z);

    particle(const particle& p);
    //void equals(particle p) const;
    //void particle::calculateDensity(particle p1, particle p2, float h);

    /** \brief Function returning the x-coordinate of the particle
     */
    float const& x() const;
    /** \brief Function returning the y-coordinate of the particle
     */
    float const& y() const;
    /** \brief Function returning the z-coordinate of the particle
     */
    float const& z() const;
    /** \brief Function returning the discrete density value of this particle
     */
    float const& density() const;
    /** \brief Function setting the discrete density value of this particle
     *  \param d density value for this particle
     */
    void setDensity(float d);

    /** \brief Function returning the 3D-coordinate of the particle
     *  \return array float with x-, y- and z-coordinate
     */
    std::array<float, 3> getArray() const;

  private:
    float x_;
    float y_;
    float z_;
    float density_;
};

#include "particle.cpp"

#endif // PARTICLE_H
