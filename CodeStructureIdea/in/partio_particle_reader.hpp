#pragma once

#include "particle_reader.hpp"

template<typename T>
class partioParticleReader : public particleReader<T> {
  public:
    partioParticleReader();

    particleList<T> read(std::string filename);
};

#include "partio_particle_reader.cpp"
