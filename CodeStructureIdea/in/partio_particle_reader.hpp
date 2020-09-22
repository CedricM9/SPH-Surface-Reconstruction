#pragma once

#include "particle_reader.hpp"

class partioParticleReader : public particleReader {
  public:
    partioParticleReader();

    particleList read(std::string filename);
};

#include "partio_particle_reader.cpp"
