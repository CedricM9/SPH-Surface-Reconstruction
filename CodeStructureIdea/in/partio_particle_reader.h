#pragma once

#include "particle_reader.h"

class partioParticleReader : public particleReader {
  public:
    partioParticleReader();

    particleList read(std::string filename);
};

#include "partio_particle_reader.cpp"
