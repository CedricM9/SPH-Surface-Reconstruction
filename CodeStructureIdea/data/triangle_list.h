#ifndef TRIANGLE_LIST_H
#define TRIANGLE_LIST_H

#include <array>
#include <vector>

#include "particle_list.h"

class triangleList : public particleList {
  public:
    triangleList();
    explicit triangleList(particleList list);
    
    void addTriangle(int index1, int index2, int index3);
    
    std::array<particle, 3> getTriangle(int index);

    std::vector<std::vector<size_t>> getFaceVector() const;

  private:
    std::vector<std::array<int, 3>> vertices_;
};

#include "triangle_list.cpp"

#endif // TRIANGLE_LIST_H
