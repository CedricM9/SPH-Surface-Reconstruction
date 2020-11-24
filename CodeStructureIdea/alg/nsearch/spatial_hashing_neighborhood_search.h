#ifndef SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H
#define SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H

#include "compact_neighborhood_search.h"

/** \class spatialHashingNeighborhoodSearch
 * \brief Class to perform compact neighborhood searches using the spatial hashing algorithm
 * \details This abstract class implements the spatial hashing compact neighborhood search
 *  provided by the library CompactNSearch.
 */
class spatialHashingNeighborhoodSearch : public compactNeighborhoodSearch {
  public:
    spatialHashingNeighborhoodSearch();

    /** \brief Function where the actual compact neighborhood search algorithm is implemented
     * \details For a given particle list and radius a list of all neighbors is returned for each particle.
     * \param list particle list to be searched
     * \param radius radius in which neighbors are searched for each particle
     */
    std::vector<std::vector<unsigned int>> find(const particleList& list, float radius);

    /** \brief Function where the actual compact neighborhood search algorithm is implemented
     * \details For a given particle list, radius and a point all neighbors for this point is returned.
     * \param list particle list to be searched
     * \param radius radius in which neighbors are searched for each particle
     * \param x x-coordinate of the point for which all neighbors have to be searched
     * \param y y-coordinate of the point for which all neighbors have to be searched
     * \param z z-coordinate of the point for which all neighbors have to be searched
     */
    std::vector<unsigned int> find(const particleList& list, float radius, float x, float y, float z);
};

#include "spatial_hashing_neighborhood_search.cpp"

#endif // SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H
