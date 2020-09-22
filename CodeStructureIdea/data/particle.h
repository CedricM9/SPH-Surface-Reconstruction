#ifndef PARTICLE_H
#define PARTICLE_H

class particle {
  public:
    particle(double x, double y, double z);

    double& x();
    double& y();
    double& z();

  private:
    double x_;
    double y_;
    double z_;
};

#include "particle.cpp"

#endif // PARTICLE_H
