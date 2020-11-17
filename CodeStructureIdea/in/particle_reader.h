#ifndef PARTICLE_READER_H
#define PARTICLE_READER_H

#include <string>

#include "reader.h"

/** \class particleReader
 * \brief Class handling the reading of different file formats for particles
 * \details This abstract class incorporates the structure common to all classes reading particle files in:
 *  partioParticleReader and vtkParticleReader implement the file formats partio and vtk.
 */
class particleReader : public reader {
  public:
    particleReader() {}
    virtual ~particleReader() = default;

    /** \brief Abstract function where the actual reading particles algorithm is implemented in the derived classes
     * \param filename name of the file with the particles to read in
     */
    virtual particleList read(std::string filename) = 0;
};

#endif // PARTICLE_READER_H
