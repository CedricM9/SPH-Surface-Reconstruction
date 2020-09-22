#pragma once

#include "compact_neighborhood_search.hpp"

template <typename T>
class spatialHashingNeighborhoodSearch : public compactNeighborhoodSearch<T> {
  public:
    spatialHashingNeighborhoodSearch();

    std::vector<std::vector<int>> find(const particleList<T>& list, T radius);
};

#include "spatial_hashing_neighborhood_search.cpp"
