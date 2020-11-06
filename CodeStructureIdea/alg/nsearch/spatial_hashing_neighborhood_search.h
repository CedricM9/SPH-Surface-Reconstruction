#ifndef SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H
#define SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H

#include "compact_neighborhood_search.h"

/** \class spatialHashingNeighborhookSearch
 * \brief Class to perform compact neighborhood searches using the spatial hashing algorithm
 * \details This abstract class implements the spatial hashing compact neighborhood search
 *  provided by the library CompactNSearch.
 */
class spatialHashingNeighborhoodSearch : public compactNeighborhoodSearch {
  public:
    spatialHashingNeighborhoodSearch();

    /** \brief Function where the actual compact neighborhood search algorithm is implemented
     * \details For a given particle list and radius a list of all neighbors is returned for each particle.
     * \param list triangle list to be searched
     * \param radius radius in which neighbors are searched for each particle
     */
    std::vector<std::vector<int>> find(const particleList& list, double radius);

    /** \brief Function where the actual compact neighborhood search algorithm is implemented
     * \details For a given particle list, radius and a particle index all neighbors for this paricle is returned.
     * \param list triangle list to be searched
     * \param radius radius in which neighbors are searched for each particle
     * \param index index of the particle in the particle list for which all neighbors have to be searched
     */
    std::vector<unsigned int> find(const particleList& list, double radius, int index);
};

#include "spatial_hashing_neighborhood_search.cpp"

#endif // SPATIAL_HASHING_NEIGHBORHOOD_SEARCH_H
