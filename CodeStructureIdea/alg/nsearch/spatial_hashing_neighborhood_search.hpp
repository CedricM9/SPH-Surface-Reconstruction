#pragma once

#include "compact_neighborhood_search.hpp"

class spatialHashingNeighborhoodSearch : public compactNeighborhoodSearch {
  public:
    spatialHashingNeighborhoodSearch();

    std::vector<std::vector<int>> find(const particleList& list, double radius);
};

#include "spatial_hashing_neighborhood_search.cpp"
