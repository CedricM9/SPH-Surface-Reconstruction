#pragma once

#include <vector>

#include "particle.hpp"

class particleList {
  public:
    particleList();
    
    void addParticle(double x, double y, double z);
    void addParticle(particle p);

    particle& getParticle(int index);

  protected:
    std::vector<particle> particles_;
};

#include "particle_list.cpp"
