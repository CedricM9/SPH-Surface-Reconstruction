#pragma once

#include <array>
#include <vector>

#include "particle_list.hpp"

class triangleList : public particleList {
  public:
    triangleList();
    explicit triangleList(particleList list);
    
    void addTriangle(int index1, int index2, int index3);
    
    std::array<particle, 3> getTriangle(int index);

  private:
    std::vector<std::array<int, 3>> vertices_;
};

#include "triangle_list.cpp"
