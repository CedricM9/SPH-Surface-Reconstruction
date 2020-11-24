#ifndef TRIANGLE_LIST_H
#define TRIANGLE_LIST_H

#include <array>
#include <vector>

#include "particle_list.h"

/** \class triangleList
 * \brief Data structure for a list of triangles
 * \details This class provides all neccessary operations for accessing and storing triangles in a list:
 *  Triangles are stored as a particle list together with 3D arrays of the particles connected to triangels
 */
class triangleList : public particleList {
  public:
    triangleList();
    explicit triangleList(particleList list);
    
    /** \brief Function adding a triangle to the list
     *  \param index1 index of the first particle in the particle list to add to the new triangle
     *  \param index2 index of the second particle in the particle list to add to the new triangle
     *  \param index3 index of the third particle in the particle list to add to the new triangle
     */
    void addTriangle(int index1, int index2, int index3);
    
    /** \brief Function returning an particle at a specific index of the list which cannot be changed
     *  \param index index of the particle in the list
     */
    std::array<particle, 3> getTriangle(int index) const;
    /** \brief Function returning an particle at a specific index of the list which cannot be changed
     *  \param index index of the particle in the list
     */
    std::array<int, 3> getTriangleIndices(int index) const;

    /** \brief Function returning the number of all triangles in the list
     */
    int getNumberOfTriangles() const;

    /** \brief Function returning all triangles as a vector of vectors
     * \return vector containing all triangles as size_t vectors with the indices of the three particles
     */
    std::vector<std::vector<size_t>> getFaceVector() const;

  private:
    std::vector<std::array<int, 3>> vertices_;
};

#include "triangle_list.cpp"

#endif // TRIANGLE_LIST_H
