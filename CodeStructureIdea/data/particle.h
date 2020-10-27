#ifndef PARTICLE_H
#define PARTICLE_H

#include<array>

class particle {
  public:
    particle();
    particle(float x, float y, float z);

    particle(const particle& p);
    //void equals(particle p) const;
    //void particle::calculateDensity(particle p1, particle p2, float h);

    float const& x() const;
    float const& y() const;
    float const& z() const;
    float const& density() const;
    void setDensity(float d);

    std::array<float, 3> getArray() const;

  private:
    float x_;
    float y_;
    float z_;
    float density_;
};

#include "particle.cpp"

#endif // PARTICLE_H
