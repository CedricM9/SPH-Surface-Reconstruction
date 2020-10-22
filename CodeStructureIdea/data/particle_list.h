#ifndef PARTICLE_LIST_H
#define PARTICLE_LIST_H

#include <vector>

#include "particle.h"

class particleList {
  public:
    particleList();
    virtual ~particleList() = default;
    
    void addParticle(float x, float y, float z);
    void addParticle(particle p);

    particle const& getParticle(int index) const;
    int getNumberOfParticles() const;

    std::vector<std::array<float, 3>> getParticleVector() const;

  protected:
    std::vector<particle> particles_;
};

#include "particle_list.cpp"

#endif // PARTICLE_LIST_H
