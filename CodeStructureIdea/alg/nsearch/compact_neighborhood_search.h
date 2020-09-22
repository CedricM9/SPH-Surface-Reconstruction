#ifndef COMPACT_NEIGHBORHOOD_SEARCH_H
#define COMPACT_NEIGHBORHOOD_SEARCH_H

#include <vector>

#include "particle_list.h"

class compactNeighborhoodSearch {
  public:
    compactNeighborhoodSearch() {}

    virtual std::vector<std::vector<int>> find(const particleList& list, double radius) = 0;
};

#endif // COMPACT_NEIGHBORHOOD_SEARCH_H
