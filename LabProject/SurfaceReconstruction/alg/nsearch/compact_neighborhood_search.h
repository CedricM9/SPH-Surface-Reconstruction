#ifndef COMPACT_NEIGHBORHOOD_SEARCH_H
#define COMPACT_NEIGHBORHOOD_SEARCH_H

#include <vector>

#include "particle_list.h"

/** \class compactNeighborhoodSearch
 * \brief Class to perform compact neighborhood searches
 * \details This abstract class defines the common structure of all classes performing compact neighborhood searches:
 *  spatialHashingNeighborhoodSearch.
 */
class compactNeighborhoodSearch {
  public:
    compactNeighborhoodSearch() {}

    /** \brief Abstract function where the actual compact neighborhood search algorithm is implemented in the derived classes
     * \param list triangle list to be searched
     * \param radius radius in which neighbors are searched for each particle
     */
    virtual std::vector<std::vector<unsigned int>> find(const particleList& list, float radius) = 0;
    virtual std::vector<unsigned int> find(const particleList& list, float radius, float x, float y, float z) = 0;
};

#endif // COMPACT_NEIGHBORHOOD_SEARCH_H
