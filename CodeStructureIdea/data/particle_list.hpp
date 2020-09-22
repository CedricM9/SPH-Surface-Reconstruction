#pragma once

#include <vector>

#include "particle.hpp"

template <typename T>
class particleList {
  public:
    particleList();
    
    void addParticle(T x, T y, T z);
    void addParticle(particle<T> p);

    particle<T>& getParticle(int index);

  protected:
    std::vector<particle<T>> particles_;
};

#include "particle_list.cpp"
