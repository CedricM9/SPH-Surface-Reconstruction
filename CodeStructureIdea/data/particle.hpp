#pragma once

template<typename T>
class particle {
  public:
    particle(T x, T y, T z);

    T& x();
    T& y();
    T& z();

  private:
    T x_;
    T y_;
    T z_;
};

#include "particle.cpp"
