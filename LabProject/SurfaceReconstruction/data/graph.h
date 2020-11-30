#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>

#include "particle_list.h"

/** \class graph
 * \brief Data structure for a voxel grid overlaying a particle set
 * \details This class creates equally sized voxels overlaying all particles in a set,
 *  a padding is added to all directions
 */
class graph {
  public:
    graph();
    graph(particleList& particles, int accuracy);
        
    /** \brief Function returning the minimum x-coordinate of all grid cells
     */
    float const& xMin() const;
    /** \brief Function returning the maximum x-coordinate of all grid cells
     */
    float const& xMax() const;
    /** \brief Function returning the maximum y-coordinate of all grid cells
     */
    float const& yMin() const;
    /** \brief Function returning the maximum y-coordinate of all grid cells
     */
    float const& yMax() const;
    /** \brief Function returning the maximum z-coordinate of all grid cells
     */
    float const& zMin() const;
    /** \brief Function returning the maximum z-coordinate of all grid cells
     */
    float const& zMax() const;

    /** \brief Function returning the size of all voxels
     */
    float const& cellSize() const;
    /** \brief Function returning the number of cells given a coordinate direction
     *  \param i index of the cooredinate direction: 0 for x-, 1 for y-, 2 for z-direction
     */
    int numCells(int i);

    //void adjustCellSize(float val);

  private:
    //float xLength, yLength, zLength;
    float xMin_, xMax_;
    float yMin_, yMax_;
    float zMin_, zMax_;

    float cellSize_;
    int numCells_[3];
};

#include "graph.cpp"

#endif // GRAPH_H
