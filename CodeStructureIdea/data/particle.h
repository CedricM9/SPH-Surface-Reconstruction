#ifndef PARTICLE_H
#define PARTICLE_H

#include<array>

class particle {
  public:
    particle();
    particle(float x, float y, float z);

    particle(const particle& p);
    //void equals(particle p) const;

    float const& x() const;
    float const& y() const;
    float const& z() const;

    std::array<float, 3> getArray() const;

  private:
    float x_;
    float y_;
    float z_;
};

#include "particle.cpp"

#endif // PARTICLE_H
