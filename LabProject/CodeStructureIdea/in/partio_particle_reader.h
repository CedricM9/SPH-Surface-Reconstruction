#ifndef PARTIO_PARTICLE_READER_H
#define PARTIO_PARTICLE_READER_H

#include <string>

#include "particle_reader.h"

/** \class partioParticleReader
 * \brief Class handling the reading of particles from the file format partio
 * \details This class reads the particle data from partio files given by their file name.
 */
class partioParticleReader : public particleReader {
  public:
    partioParticleReader();

    /** \brief Function where the actual reading particles algorithm from partio files is implemented
     * \param filename name of the partio file with the particles to read in
     */
    particleList read(const std::string &filename);
};

#include "partio_particle_reader.cpp"

#endif // PARTIO_PARTICLE_READER_H
