#pragma once

#include <array>
#include <vector>

#include "particle_list.hpp"

template <typename T>
class triangleList : public particleList<T> {
  public:
    triangleList();
    explicit triangleList(particleList<T> list);
    
    void addTriangle(int index1, int index2, int index3);
    
    std::array<particle<T>, 3> getTriangle(int index);

  private:
    std::vector<std::array<int, 3>> vertices_;
};

#include "triangle_list.cpp"
