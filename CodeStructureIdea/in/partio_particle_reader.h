#ifndef PARTIO_PARTICLE_READER_H
#define PARTIO_PARTICLE_READER_H

#include "particle_reader.h"

class partioParticleReader : public particleReader {
  public:
    partioParticleReader();

    particleList read(std::string filename);
};

#include "partio_particle_reader.cpp"

#endif // PARTIO_PARTICLE_READER_H
