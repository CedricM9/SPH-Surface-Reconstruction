#ifndef PARTICLE_H
#define PARTICLE_H

#include<array>

class particle {
  public:
    particle(double x, double y, double z);

    double const& x() const;
    double const& y() const;
    double const& z() const;

    std::array<double, 3> getArray() const;

  private:
    double x_;
    double y_;
    double z_;
};

#include "particle.cpp"

#endif // PARTICLE_H
