#ifndef PARTICLE_LIST_H
#define PARTICLE_LIST_H

#include <vector>

#include "particle.h"

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

#endif // PARTICLE_LIST_H
