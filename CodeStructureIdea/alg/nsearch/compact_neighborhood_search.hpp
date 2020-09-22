#pragma once

#include <vector>

#include "particle_list.hpp"

class compactNeighborhoodSearch {
  public:
    compactNeighborhoodSearch() {}

    virtual std::vector<std::vector<int>> find(const particleList& list, double radius) = 0;
};

