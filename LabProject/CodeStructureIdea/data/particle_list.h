#ifndef PARTICLE_LIST_H
#define PARTICLE_LIST_H

#include <vector>

#include "particle.h"

/** \class particleList
 * \brief Data structure for a list of particles
 * \details This class provides all neccessary operations for accessing and storing particles in a list.
 */
class particleList {
  public:
    particleList();
    virtual ~particleList() = default;
    
    /** \brief Function adding a particle from coordinates to the list
     *  \param x x-coordinate of the particle to create and add
     *  \param y y-coordinate of the particle to create and add
     *  \param z z-coordinate of the particle to create and add
     */
    void addParticle(float x, float y, float z);
    /** \brief Function adding an already existing particle to the list
     *  \param p particle to add
     */
    void addParticle(particle p);
    /** \brief Function adding an already existing particle to the list if it is not in there yet
     *  \param p particle to add
     *  \return index of the already existing particle in the list
     */
    int addParticleWithCheck(particle p);
    void removeParticle();

    /** \brief Function returning an particle at a specific index of the list which can be changed
     *  \param index index of the particle in the list
     */
    particle& getParticle(int index);
    /** \brief Function returning an particle at a specific index of the list which cannot be changed
     *  \param index index of the particle in the list
     */
    particle getParticle(int index) const;
    /** \brief Function returning the number of all particles in the list
     */
    int getNumberOfParticles() const;

    /** \brief Function returning all particles as a vector of 3D arrays
     * \return vector containing all particles as float arrays with x-, y- and z-coordinate
     */
    std::vector<std::array<float, 3>> getParticleVector() const;

  protected:
    std::vector<particle> particles_;
};

#include "particle_list.cpp"

#endif // PARTICLE_LIST_H
