#pragma once

#include <vector>

#include "particle_list.hpp"

template <typename T>
class compactNeighborhoodSearch {
  public:
    compactNeighborhoodSearch() {}

    virtual std::vector<std::vector<int>> find(const particleList<T>& list, T radius) = 0;
};

